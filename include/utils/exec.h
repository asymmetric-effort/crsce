/**
 * @file include/utils/exec.h
 * @brief Helper function to execute a command and capture stdout
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */
#pragma once

#include <string>
#include <array>

namespace utils {
    /**
     * @name exec
     * @brief execute a given string and return the command output (stdout)
     * @param cmd std::string&
     * @return std::string
     */
    static std::string exec(const std::string& cmd) {
        std::array<char, 256> buffer;
        std::string result;
        const std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), &pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (size_t n = fread(buffer.data(), 1, buffer.size(), pipe.get()); n > 0)
                result.append(buffer.data(), n);
        }
        return result;
    }
}
