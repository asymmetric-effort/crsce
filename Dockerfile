FROM ubuntu:latest AS base
ENV DEBIAN_FRONTEND=noninterative
WORKDIR /opt/
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y build-essential \
                       docker.io \
                       cmake \
                       ccache \
                       clang \
                       libc++-dev \
                       libc++abi-dev \
                       make \
                       time \
                       ninja-build \
                       curl \
                       libssl-dev \
                       pkg-config \
                       cppcheck \
                       python3 \
                       python3-pip && \
    pip install --break-system-packages \
                pymarkdown \
                yamllint \
                json-linter && \
    ln -s /usr/local/bin/json-linter /usr/local/bin/jsonlint

FROM base AS builder
COPY . /opt/

