`Gpu::Ipc::Communications`
==========================

## Purpose
Operates an InterProcess Communications hub between a parent and child process.

## Properties

| Property          | Type                | Description                                            |
|-------------------|---------------------|--------------------------------------------------------|
| `parentToChildFd` | file descriptor     | parent to child local read/write file descriptor       |
| `childToParentFd` | file descriptor     | child to parent local read/write file descriptor       |
| `parentPid`       | `pid_t`             | PID of the parent process                              |
| `childPid`        | `pid_t`             | PID of the child process                               |
| `isParent`        | `bool`              | True if this instance is running in the parent process |
| `shutdownFlag`    | `std::atomic<bool>` | True indicates that shutdown is in progress            |

## Methods (public)

| Method | Returns  | Arguments   | Description                                     |
|--------|----------|-------------|-------------------------------------------------|
| `send` | `Result` | `Message&`  | parent process can send `Message` to child      |
| `send` | `Result` | `Response&` | child process can send `Response` to parent     |
| `recv` | `Result` | `Message&`  | child process can receive `Message` from parent |
| `recv` | `Result` | `Response&` | parent process can receive `Message` from child |

## Methods (private)

| Method                 | Returns | Arguments | Description                                           |
|------------------------|---------|-----------|-------------------------------------------------------|
| `validateParentAccess` | `bool`  | none      | verify send/recv permission based on parent/child pid |
| `validateChildAccess`  | `bool`  | none      | verify send/recv permission based on parent/child pid |
