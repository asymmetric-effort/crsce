FROM ubuntu:latest AS base
ENV DEBIAN_FRONTEND=noninterative
WORKDIR /opt/
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y build-essential \
                       ccache \
                       clang \
                       cmake \
                       cppcheck \
                       curl \
                       libc++-dev \
                       libc++abi-dev \
                       libssl-dev \
                       make \
                       ninja-build \
                       pkg-config \
                       python3 \
                       python3-pip \
                       time && \
    pip install --break-system-packages \
                json-linter \
                pymarkdown \
                yamllint && \
    rm -rf /var/lib/apt/lists/* /var/cache/apt/archives/*

FROM base AS builder
COPY . /opt/

