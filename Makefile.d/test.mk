# clean.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

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
