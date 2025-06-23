# build.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: lint/json
lint/json:
	@echo "$@: starting"
	@( \
		for i in $$(find . \( -path './cmake-build-*' -o -path './build' \) -prune -type f -name '*.json'); do \
		    json-linter filename $${i} || exit 1; \
		done; \
	)
	@echo "$@: ok"
