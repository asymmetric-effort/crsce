# docker.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: docker
docker:
	@docker build --tag builder:latest .
