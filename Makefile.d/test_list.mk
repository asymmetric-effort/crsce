# Makefile.d/test_list.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

test/list: configure
	cmake --build build --target list_tests
