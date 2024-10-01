BUILD_DIR=$(CURDIR)/build

.PHONY: build
build:
	cmake -B '$(BUILD_DIR)' -S '$(CURDIR)' -G Ninja \
		  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		  -DCMAKE_BUILD_TYPE=Debug && \
		ninja -C '$(BUILD_DIR)'

.PHONY: clean
clean:
	rm -rf '$(BUILD_DIR)'
