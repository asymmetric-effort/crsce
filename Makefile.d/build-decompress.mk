# build-decompress.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: build-decompress
build-decompress: configure
	@cmake --build build --target decompress
