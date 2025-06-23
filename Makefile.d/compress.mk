# compress.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: compress
compress:
	@rm build/compress.crsce.out &> /dev/null || true
	./build/bin/compress --in build/bin/compress --out build/compress.crsce.out
