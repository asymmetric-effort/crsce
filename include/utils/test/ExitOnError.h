/**
 * @file include/utils/test/ExitOnError.h
 * @brief define a boolean type representing how tests should behave on error.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

using ExitOnError = bool;
constexpr ExitOnError TerminateOnError=true;
constexpr ExitOnError ThrowExceptionOnError=false;
