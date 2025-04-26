#include "utils/Arguments/Arguments.h"

const std::string get(const std::string &name) const {
    auto it = data.find(name);
    if (it != data.end()) {
        return it->second;
    }
    throw ArgumentsException("No such argument: " + name);
}