// file: include/utils/test/ExitOnError.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

using ExitOnError = bool;
constexpr ExitOnError TerminateOnError=true;
constexpr ExitOnError ThrowExceptionOnError=false;
