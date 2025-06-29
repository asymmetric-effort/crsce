# zip.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: zip
zip: tree
	@echo 'create build/project_files.zip'
	zip -r ./build/project.zip . \
		-x ".git/*" \
		-x "build/*" \
		-x ".venv/*" \
		-x ".idea/*" \
		-x ".DS_Store"
