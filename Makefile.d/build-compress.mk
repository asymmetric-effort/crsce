# build-compress.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: build-compress
build-compress: configure
	@cmake --build build --target compress
