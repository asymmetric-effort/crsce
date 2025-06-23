# build.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: lint
lint: lint/json lint/yaml lint/cpp
	@echo "lint: ok"
