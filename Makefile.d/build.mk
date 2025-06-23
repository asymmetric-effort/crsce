# build.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: build
build: configure
	@time cmake --build build --target build_all -- $(cat build/concurrency.build.flag)
