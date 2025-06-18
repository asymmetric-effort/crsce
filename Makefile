.PHONY: configure
configure:
	@cmake -G Ninja -S . -B build

.PHONY: lint
lint: configure
	@time cmake --build build --target linters

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
