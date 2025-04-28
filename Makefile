# file: Makefile
.PHONY: build clean configure

tree:
	@tree > build/file_structure.txt

zip:
	zip -r build/project_files.zip .

clean:
	@rm -rf ./build &> /dev/null || true

configure:
	@cmake -S . -B build

build: configure
	@cmake --build build --target build_all

build-compress: configure
	@cmake --build build --target compress

build-decompress: configure
	@cmake --build build --target decompress

test_compress_flag_usage:
	./build/test/test_compress_flag_usage

test_compress_flag_version:
	./build/test/test_compress_flag_version

test_decompress_flag_usage:
	./build/test/test_decompress_flag_usage

test_decompress_flag_version:
	./build/test/test_decompress_flag_version

test_cross_sum_value:
	./build/test/test_CrossSumValue

test: test_compress_flag_usage \
	  test_compress_flag_version \
	  test_decompress_flag_usage \
	  test_decompress_flag_version \
	  test_cross_sum_value
	  @echo 'ok'

compress:
	@rm build/compress.crsce.out &> /dev/null || true
	./build/bin/compress --in build/bin/compress --out build/compress.crsce.out

decompress: compress
	@rm build/decompress.crsce.out &> /dev/null || true
	./build/bin/decompress --in build/compress.crsce.out --out build/decompress.crsce.out
