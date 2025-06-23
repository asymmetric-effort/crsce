# build.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

lint/yaml:
	@echo "$@: starting"
	find . -type f \( -name '*.yml' -o -name '*.yaml' \) -print0 | xargs -0 -n1 yamllint
	@echo "$@: ok"
