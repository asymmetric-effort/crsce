#include "utils/Exceptions/MissingArguments.h"

namespace Exceptions{
    const char* Exceptions::MissingArguments::what() const noexcept override {
        return message.c_str();
    }
}
