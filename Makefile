# file: Makefile
.PHONY: build clean configure

clean:
	@rm -rf ./build &> /dev/null || true

configure:
	@cmake -S . -B build

build: configure
	@cmake --build build --target build_all

test_flag_usage:
	./build/test_flag_usage

test_flag_version:
	./build/test_flag_version

test: test_flag_usage \
	  test_flag_version
