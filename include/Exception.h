#ifndef BC_EXCEPTION_H
#define BC_EXCEPTION_H 1

#include <exception>
#include <string>

namespace BC
{
class Exception : public std::exception
{
public:
  Exception(const std::string &str) : m_str(str) { }
  virtual ~Exception() throw() { }
  virtual const char *what() const throw() { return m_str.c_str(); }
private:
  std::string m_str;
};
}

#endif //BC_EXCEPTION_H
