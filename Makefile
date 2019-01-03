.PHONY: build
build:
	@cd build && cmake .. && make libcppcore

.PHONY: test
test:
	@cd build && cmake .. && make test_all && ./test_all --gtest_output=xml

.PHONY: install
install:
	@cd build && cmake .. && make install

.PHONY: docs
docs:
	@doxygen Doxyfile
	@moxygen -o docs/markdown.md -a docs/xml

	