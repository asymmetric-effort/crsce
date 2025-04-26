.PHONY:build
.PHONY:clean
.PHONY:configure

clean:
	@rm -rf ./build &> /dev/null || true
	@rm -f CMakeCache.txt &> /dev/null || true

configure:
	# Configure CMake project
	cmake -S . -B build

build:
	cmake --build build --target build_all
