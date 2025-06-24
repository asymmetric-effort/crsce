`Gpu::Ipc::Communications`
==========================

## Purpose

Operates an InterProcess Communications hub between a parent and child process.

## Properties

| Property          | Type                | Description                                            |
|-------------------|---------------------|--------------------------------------------------------|
| `parentToChildFd` | file descriptor     | parent to child local read/write file descriptor       |
| `childToParentFd` | file descriptor     | child to parent local read/write file descriptor       |

### Notes

* For `parentToChildFd` and `childToParentFd`, "[0] is the read end, [1] is the write end, consistent with pipe()
  behavior."

## Methods (public)

| Method | Returns            | Arguments   | Description                                     |
|--------|--------------------|-------------|-------------------------------------------------|
| `send` | `Gpu::Ipc::Result` | `Message&`  | parent process can send `Message` to child      |
| `send` | `Gpu::Ipc::Result` | `Response&` | child process can send `Response` to parent     |
| `recv` | `Gpu::Ipc::Result` | `Message&`  | child process can receive `Message` from parent |
| `recv` | `Gpu::Ipc::Result` | `Response&` | parent process can receive `Message` from child |
