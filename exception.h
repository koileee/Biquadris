#include <iostream>
#include <exception>
#include <string>



class GameOver : public std::exception
{
  std::string msg;
public:
  GameOver(std::string const &msg) : msg(msg) {}
  GameOver(char const * msg) : msg(msg) {}
  const char* what() const noexcept override { return msg.c_str(); }
};


class SwitchPlayer : public std::exception
{
  std::string msg;
public:
  SwitchPlayer(std::string const &msg) : msg(msg) {}
  SwitchPlayer(char const * msg) : msg(msg) {}
  const char* what() const noexcept override { return msg.c_str(); }
};



class SpecialAction : public std::exception
{
  std::string msg;
public:
  SpecialAction(std::string const &msg) : msg(msg) {}
  SpecialAction(char const * msg) : msg(msg) {}
  const char* what() const noexcept override{ return msg.c_str(); }
};
