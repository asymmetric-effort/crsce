GPU Emulator IPC Protocol Specification
=======================================

## Overview

This document defines the full architecture of a mock GPU emulator for the CRSCE project. The design
simulates concurrent GPU kernel execution using a child process that emulates GPU behavior. The emulator
supports real-time interprocess communication (IPC) with a parent process, allowing command dispatch,
memory management, and kernel task execution through a well-defined protocol.



## Types

## Classes


### Class: `Gpu::Device::MockGpu`
#### Purpose
Entry point in child process


Responsibilities:

Loop over IPC commands

Dispatch to runtime

Return responses

RuntimeManager Class

Created inside MockGpu

Responsibilities:

Implements command handlers:

handleAlloc()

handleFree()

handleRegisterKernel()

handleLaunchTask()

handleReset()

handleShutdown()

Launches and manages kernel threads

Owns ThreadRegistry

Owns KernelManager

ThreadRegistry Class

Encapsulated thread-safe thread tracking utility

API:

void insert(uint32_t launchId, std::thread&&)

void joinAll()

void clear()

Used by RuntimeManager to track in-flight kernel executions

KernelManager Class

Tracks registered kernels and dispatches them

Stores kernel blobs indexed by kernelId

API:

void registerKernel(uint32_t kernelId, std::vector<uint8_t> binary)

void run(uint32_t kernelId, const std::vector<uint8_t>& args)

Kernel Execution

Each LaunchTask spawns a new detached thread via RuntimeManager

Thread executes a registered kernel using its binary blob

Thread is registered via ThreadRegistry

Shutdown Lifecycle

Gpu::Device::Emulator::shutdown()

Sends Shutdown message

Waits on child process

MockGpu::handleShutdown()

Sets atomic shutdown flag

Joins all active threads

Clears memory

Returns status=0 on success

Reset Lifecycle

Similar to shutdown

Resets memory and thread registry

Keeps process alive and re-usable

IPC Commands Summary

Command

Description

Alloc

Allocate GPU memory

Free

Free allocated GPU memory

Write

Copy data to GPU memory

Read

Copy data from GPU memory

RegisterKernel

Register binary blob for kernel execution

LaunchTask

Launch kernel in concurrent thread

Reset

Clear memory and join all threads

Shutdown

Terminate all threads and exit gracefully

Compliance with GPU Semantics

Kernel concurrency mimics CUDA/HIP/Metal streams

KernelManager abstraction allows task-based dispatch

ThreadRegistry ensures safe and debuggable concurrency model

Emulates unified memory view via pointer tracking

