#ifndef BC_PARSE_CMD_OPTIONS_H
#define BC_PARSE_CMD_OPTIONS_H

#include <string>
#include <vector>

namespace BC
{
  class CmdOptBase;
}

namespace BC
{
  /// \brief class ParseCmdOptions is for parsing command arguments
  class ParseCmdOptions
  {
   private:
    ParseCmdOptions(const ParseCmdOptions&);
    ParseCmdOptions& operator=(const ParseCmdOptions&);
   public:
    /// \brief default constructor
    ParseCmdOptions();

    /// \brief destructor
    ~ParseCmdOptions();

    /// \brief add description for command like '-n' or '-n name'
    /// \param opt is an option in command line
    /// \param descr is a description for current option
    /// \param alias for current option - usually one word
    /// \param isRequired defines is this option is required
    /// \param isWithValue shows if current option needs a value: "-h"(no value) or "-f filename"(with value)
    void addOption(char opt, const std::string & descr, const std::string & alias, bool isRequired, bool isWithValue);

    /// \brief add description for command like '-n name'
    /// \param opt is an option in command line
    /// \param descr is a description for current option
    /// \param alias for current option - usually one word
    /// \param isRequired defines is this option is required
    /// \param ref is a reference to parameter which will be updated after processCmdOptions function call if parameter will be found
    void addOption(char opt, const std::string & descr, const std::string & alias, bool isRequired, std::string &ref);

    /// \brief process command options
    /// \param count count of command line(like in main function)
    /// \param args array of command arguments(like in main function)
    /// \param[out] errMsg error message in cases if not required parameters have been filled or there is no such options in our description
    /// \return true on success, false otherwise, on false you can check errMsg
    bool processCmdOptions(unsigned int count, char ** args, std::string &errMsg);

    /// \brief get programm name
    /// \return programm name
    inline std::string getProgramName( ) const { return programName_; }

    /// \brief sets programm name
    inline void setProgramName(const std::string &programName) { programName_ = programName; }

    /// \bried check if option was in program arguments
    /// \param option option
    /// \return true if option was in program arguments, false otherwise
    bool checkOption(char option) const;
    
    /// \brief get value of specified option
    ///        if you added option without reference to update, you can get options with current method
    /// \param option is an option from command line
    /// \param[out] is a value for specified option
    /// \return true if option has been found, false otherwise
    bool get(char option, std::string & value) const;

    /// \brief get all other unprocessed values. Example: 'a.exe -p param1 -n name UNPROC1 -f -d data UNPROC2'
    ///        for this command line function returns array with UNPROC1 and UNPROC2 values
    /// \return array of unprocessed values in command line
    inline const std::vector<std::string> & getUnprocessedValues() const { return unprocessed_; }

    /// \brief get full description for current object like help
    /// \param[out] info information current object like help
    void getInfo( std::string & info ) const;

    /// \brief add examle of command usage
    /// \param example example of usage
    inline void addExample(const std::string &example, const std::string &cmdLine) { examples_.push_back( std::pair<std::string,std::string>(example, cmdLine) ); }

    /// \brief add description of program
    /// \param descr descriptoin
    inline void addDescription(const std::string &descr) { descr_ += descr; }

   //members
   private:
    std::string descr_;
    std::vector<CmdOptBase*> cmdOptions_;
    std::string programName_;
    std::vector<std::string> unprocessed_;
    std::vector<std::pair<std::string,std::string> > examples_;
  };
};

#endif //BC_PARSE_CMD_OPTIONS_H
