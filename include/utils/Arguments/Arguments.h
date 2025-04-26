#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <map>
#include <string>
#include <exception>
#include "utils/Exceptions/MissingArguments.h"

class Arguments{

public:

  Arguments(int argc, char *argv[]);

  ~Arguments();

  const std::string get(const std::string &name) const;

private:

  std::map<std::string, std::string> data;

};

#endif //ARGUMENTS_H