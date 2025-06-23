# clean.mk
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

.PHONY: tree
tree:
	@echo 'create build/file_structure.txt'
	@treehash > build/file_structure.txt
	#@tree > build/file_structure.txt
