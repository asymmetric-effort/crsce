# lint_py.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

lint/py:
	@flake8
	@echo "$@: ok"
