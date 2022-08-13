NAME := app

-include script/build.mk

CFLAGS += -flto -Og -ggdb3 -fsanitize=address
LDFLAGS += -flto -Og -ggdb3 -fsanitize=address

.PHONY: run pre

OUTPUT_PATH := $(BUILD_DIR)/output

run:$(BINARY)
	@mkdir -p $(OUTPUT_PATH)
	@$(BINARY) $(ARG)


# vs code clangd use compile_commands.json to work
pre:
	@echo + compile_commands.json
	@compiledb -n make run
