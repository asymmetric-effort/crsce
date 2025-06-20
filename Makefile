.PHONY: configure
configure:
	@cmake -G Ninja -S . -B build

.PHONY: lint
lint: lint/json lint/yaml lint/cpp
	@echo "lint: ok"

.PHONY: lint/json
lint/json:
	@echo "$@: starting"
	@( \
		for i in $$(find . \( -path './cmake-build-*' -o -path './build' \) -prune -type f -name '*.json'); do json-linter filename $${i}; done; \
	)
	@echo "$@: ok"

lint/yaml:
	@echo "$@: starting"
	find . -type f \( -name '*.yml' -o -name '*.yaml' \) -print0 | xargs -0 -n1 yamllint
	@echo "$@: ok"

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


.PHONY: build
build: configure
	@time cmake --build build --target build_all

.PHONY: build-decompress
build-decompress: configure
	@cmake --build build --target decompress

.PHONY: build-compress
build-compress: configure
	@cmake --build build --target compress

.PHONY: compress
compress:
	@rm build/compress.crsce.out &> /dev/null || true
	./build/bin/compress --in build/bin/compress --out build/compress.crsce.out

.PHONY: test
test:
	@echo "running tests"; \
	for f in ./build/test/*; do \
		echo "Running: $$f"; \
		"$$f"; \
		if [ $$? -ne 0 ]; then \
			echo "[FAIL] Test $$f failed. Aborting."; \
			exit 1; \
		fi; \
	done; \
	echo "[PASS] All tests passed."

.PHONY: zip
zip: tree
	@echo 'create build/project_files.zip'
	zip -r ./build/project.zip . -x ".git/*" "build/*"

.PHONY: tree
tree:
	@echo 'create build/file_structure.txt'
	@treehash > build/file_structure.txt
	#@tree > build/file_structure.txt

.PHONY: decompress
decompress: compress
	@rm build/decompress.crsce.out &> /dev/null || true
	./build/bin/decompress --in build/compress.crsce.out --out build/decompress.crsce.out

.PHONY: clean
clean:
	@rm -rf ./build &> /dev/null || true
	@mkdir -p ./build &> /dev/null || true

.PHONY: docker
docker:
	@docker build --tag builder:latest .
