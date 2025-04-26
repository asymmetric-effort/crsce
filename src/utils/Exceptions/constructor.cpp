#include "utils/Exceptions/MissingArguments.h"

namespace Exceptions{
    MissingArguments::MissingArguments(const std::string& msg) : message(msg) {
        // Do nothing
    }
}