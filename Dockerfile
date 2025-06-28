# Dockerfile
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#
# Base image
#
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

#
# Project Automation Image
#
FROM base AS project_automation
COPY tools/project-automation/requirements.txt /opt/requirements.txt
COPY tools/project-automation/project-automation.py /opt/project-automation.py
RUN pip install --break-system-packages -r /opt/requirements.txt
ENTRYPOINT [ "python3","/opt/project-automation.py" ]

#
# C++ Builder Image
#
FROM base AS builder
COPY . /opt/
