#include <algorithm>
#include <functional>
#include "ParseCmdOptions.h"

namespace BC
{
  class CmdOptBase
  {
   private:
    CmdOptBase();                             
    CmdOptBase(const CmdOptBase&);              
    CmdOptBase& operator=(const CmdOptBase&);
   public:
    CmdOptBase(char opt, const std::string & descr, const std::string & alias, bool isRequired, bool isWithValue)
      : opt_(opt), descr_(descr), alias_(alias), isRequired_(isRequired), isFound_(false), isWithValue_(isWithValue) { }
    inline bool isFound() const { return isFound_; }
    inline bool isRequired() const { return isRequired_; }
    inline bool isWithValue() const { return isWithValue_; }
    inline char getOption() const { return opt_; }
    inline const std::string & getValue() const { return val_; }
    inline const std::string & getAlias() const { return alias_; }
    inline const std::string & getDescription() const { return descr_; }
    virtual void fill(const std::string &val) { isFound_ = true; val_ = val; }
   protected:
    char opt_;
    std::string descr_;
    bool isRequired_;
    bool isWithValue_;
    bool isFound_;
    std::string val_;
    std::string alias_;
  };

  class CmdOptWithValue : public CmdOptBase
  {
   private:
    CmdOptWithValue();                             
    CmdOptWithValue(const CmdOptWithValue&);              
    CmdOptWithValue& operator=(const CmdOptWithValue&);
   public:
    CmdOptWithValue(char opt, const std::string & descr, const std::string & alias, bool isRequired, std::string &ref)
      : CmdOptBase(opt, descr, alias, isRequired, true), ref_(ref) { }
    virtual void fill(const std::string &val) { isFound_ = true; val_ = val; ref_ = val; }
   protected:
    std::string &ref_;
  };

  //template functor
  struct CmpCmdOptBasePtr : public std::unary_function<CmdOptBase*, bool>
  {
    CmpCmdOptBasePtr(char opt) : opt_(opt) { }

    bool operator()(const CmdOptBase *cmdOpt) const
    {
      return (cmdOpt && cmdOpt->getOption() == opt_);
    }

    char opt_;
  };
};



namespace BC 
{
  ParseCmdOptions::ParseCmdOptions() { }

  bool ParseCmdOptions::processCmdOptions(unsigned int count, char ** begin, std::string &errMsg) 
  {
    errMsg.clear();
    this->setProgramName(begin[0]);
    std::string str, val;
    for (unsigned int i=1; i < count; ++i)
    {
      str = begin[i];
      if (str.size() > 1 && str[0] == '-' )
      {
        char opt = str[1];
        std::vector<CmdOptBase*>::iterator it = std::find_if(cmdOptions_.begin(), cmdOptions_.end(), CmpCmdOptBasePtr(opt));
        if (it != cmdOptions_.end())
        {
          CmdOptBase *cmdOpt = *it;
          if (cmdOpt->isFound())
          {
            errMsg += std::string("Optoin -") + opt + " already has been set. ";
            break;
          }
          //set value if needed
          val.clear();
          if (cmdOpt->isWithValue())
          {
            if (str.size() > 2) val = str.substr(2);
            else if (i+1 < count && std::string(begin[i+1])[0] != '-') val = begin[++i];
            else errMsg += std::string("Can't find a value of option -") + opt + std::string(". ");
          }
          cmdOpt->fill(val);
        }
        else
        {
          errMsg += std::string("Option -") + opt + " is unknown. ";
          break;
        }
      }
      else unprocessed_.push_back(str);
    }

    //check that we found all required parameters
    std::vector<CmdOptBase*>::const_iterator from=cmdOptions_.begin(), end=cmdOptions_.end();
    for ( ; from!=end; ++from )
    {
      const CmdOptBase *cmdOpt = *from;
      if (cmdOpt->isRequired() && !cmdOpt->isFound())
      {
        errMsg += std::string("Option -") + cmdOpt->getOption() + " is required. ";
        break;
      }
    }

    return errMsg.empty();
  }


  ParseCmdOptions::~ParseCmdOptions()
  {
    std::vector<CmdOptBase*>::iterator from=cmdOptions_.begin(), end=cmdOptions_.end();
    for ( ; from!=end; ++from)
    {
      delete *from;
    }
  }


  void ParseCmdOptions::addOption(char opt, const std::string & descr, const std::string & alias, bool isRequired, bool isWithValue)
  {
    cmdOptions_.push_back (new CmdOptBase(opt, descr, alias, isRequired, isWithValue));
  }


  void ParseCmdOptions::addOption(char opt, const std::string & descr, const std::string & alias, bool isRequired, std::string &ref)
  {
    cmdOptions_.push_back (new CmdOptWithValue(opt, descr, alias, isRequired, ref));
  }


  bool ParseCmdOptions::checkOption(char option) const
  {
    std::vector<CmdOptBase*>::const_iterator it = std::find_if(cmdOptions_.begin(), cmdOptions_.end(), CmpCmdOptBasePtr(option));
    if (cmdOptions_.end() == it || !(*it)->isFound()) return false;
    return true;
  }


  bool ParseCmdOptions::get(char option, std::string & value) const
  {
    value.clear();
    bool retVal = false;
    std::vector<CmdOptBase*>::const_iterator it = std::find_if(cmdOptions_.begin(), cmdOptions_.end(), CmpCmdOptBasePtr(option));
    if (it != cmdOptions_.end())
    {
      const CmdOptBase * cmdOpt = *it;
      if (cmdOpt->isFound())
      {
        retVal = true;
        value = cmdOpt->getValue();
      }
    }
    return retVal;
  }


  void ParseCmdOptions::getInfo(std::string & info) const
  {
    info.clear();
    //print program name
    info += std::string("NAME\n\t") + programName_ + std::string("\n");
    //print short synopsis with options and description
    info += std::string("SYNOPSIS\n\t") + programName_ + " ";
    std::string description = descr_.empty() ? "" : (std::string("\nDESCRIPTION\n\t") + descr_);
    std::string optDescr = description + std::string("\nOPTIONS");
    std::vector<CmdOptBase*>::const_iterator from = cmdOptions_.begin(), end = cmdOptions_.end();
    for ( ; from!=end; ++from)
    {
      const CmdOptBase *cmdOpt = *from;
      std::string brackets = cmdOpt->isRequired() ? "<>" : "[]";
      std::string alias = cmdOpt->isWithValue() ? std::string(" ") + cmdOpt->getAlias() + std::string(" ") : " ";
      info += brackets[0] + std::string(" -") + cmdOpt->getOption() + alias + brackets[1] + std::string("  ");
      optDescr += std::string ("\n\t-") + cmdOpt->getOption() + alias + std::string("\n\t\t") + cmdOpt->getDescription();
    }
    info += optDescr;
    //print examples
    if (!examples_.empty())
    {
      info += "\nEXAMPLES";
      std::vector<std::pair<std::string,std::string> >::const_iterator from = examples_.begin(), end = examples_.end();
      for ( ; from!=end; ++from )
      {
        info += std::string("\n\t") + from->first + std::string("\n\t\t") + from->second;
      }
    }
  }

};

