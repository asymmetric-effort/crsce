# file: Makefile
.PHONY: build clean configure

clean:
	@rm -rf ./build &> /dev/null || true

configure:
	@cmake -S . -B build

build: configure
	@cmake --build build --target build_all

test_compress_flag_usage:
	./build/test_compress_flag_usage

test_compress_flag_version:
	./build/test_compress_flag_version

test: test_compress_flag_usage \
	  test_compress_flag_version
