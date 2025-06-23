# clean.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: decompress
decompress: compress
	@rm build/decompress.crsce.out &> /dev/null || true
	./build/bin/decompress --in build/compress.crsce.out --out build/decompress.crsce.out
