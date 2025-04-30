// file: include/utils/get_tmp_dir.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef GET_TMP_DIR_H
#define GET_TMP_DIR_H

#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string get_tmp_dir();

#endif //GET_TMP_DIR_H