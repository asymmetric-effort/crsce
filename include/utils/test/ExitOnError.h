// file: include/utils/test/ExitOnError.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

typedef bool ExitOnError;
constexpr ExitOnError TerminateOnError=true;
constexpr ExitOnError NoTerminateOnError=false;
