#ifndef BC_LOGGER_H
#define BC_LOGGER_H 1

#include <string>
#include <iostream>
#include <fstream>

namespace BC
{

class Logger
{
public:
  static Logger &GetInstance()
  {
    static Logger instance;
    return instance;
  }

  inline void StartLog(const std::string &fName)
  {
    this->StopLog();
    m_log.open(fName.c_str());
    if (m_log.is_open())
    {
      (*this) << "Log started" << std::endl;
    }
  }

  inline void StopLog()
  {
    if (m_log.is_open())
    {
      (*this) << "Log stopped" << std::endl;
    }
  }

  ~Logger()
  {
    this->StopLog();
  }

  template<typename T>
  Logger &operator <<(const T &t)
  {
    if (m_log.is_open()) m_log << t;
    return *this;
  }

  typedef std::basic_ostream<char, std::char_traits<char> > StdStream;
  typedef StdStream& (*StandardEndLine)(StdStream&);
  Logger& operator<<(StandardEndLine manipulator)
  {
    if (m_log.is_open()) manipulator(m_log);
    return *this;
  }


private:
  Logger() {};
  Logger(Logger const &);
  Logger &operator =(Logger const &);


private:
  std::ofstream m_log;
};

}


#endif //BC_LOGGER_H
