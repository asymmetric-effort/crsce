# configure.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: configure
configure:
	@cmake -G Ninja -S . -B build
