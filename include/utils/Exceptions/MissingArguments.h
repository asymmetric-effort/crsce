#ifndef MISSING_ARGUMENTS_H
#define MISSING_ARGUMENTS_H

#include <exception>
#include <string>

namespace Exceptions{
    /**
     * @brief Exception class for missing arguments.
     */
    class MissingArguments : public std::exception {
    public:
        /**
         * @brief Construct a new MissingArguments exception with a message.
         *
         * @param msg Error message describing the missing argument.
         */
        explicit MissingArguments(const std::string &msg);

        /**
         * @brief Default destructor.
         */
        ~MissingArguments() noexcept override = default;

        /**
         * @brief Retrieve the exception message.
         *
         * @return const char* C-string containing the exception message.
         */
        const char* what() const noexcept override;

    private:
        std::string message;
    };

};
#endif //MISSING_ARGUMENTS_H