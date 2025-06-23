# build.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: lint/cpp
lint/cpp:
	@echo "$@: starting"
	@find ./include ./src ./test \
	  -type f \( -name '*.cpp' -o -name '*.h' \) -print0 \
	  | xargs -0 -n1 sh -c '\
	      cppcheck --enable=all \
	        --platform=unix64 \
	        --std=c++20 \
	        --language=c++ \
	        --suppressions-list=.cppcheck-suppressions.txt \
	        --inline-suppr \
	        --error-exitcode=2 \
	        --check-level=normal \
	        -I include/ "$$1" || exit 255\
	    ' dummy
	@echo "$@: ok"
