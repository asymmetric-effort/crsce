# clean.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: clean
clean:
	@rm -rf ./build &> /dev/null || true
	@rm -rf ./cmake-build-debug &> /dev/null || true
	@rm -rf ./cmake-build-default &> /dev/null || true
	@rm -rf ./cmake-build-release &> /dev/null || true
	@mkdir -p ./build &> /dev/null || true
