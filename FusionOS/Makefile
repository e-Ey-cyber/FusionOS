CC = gcc
CFLAGS = -Wall -Wextra -I$(SRC_DIR) `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC_DIR = system/core
BUILD_DIR = build
SOURCES = $(SRC_DIR)/init.c $(SRC_DIR)/setup.c $(SRC_DIR)/security.c \
          $(SRC_DIR)/network.c $(SRC_DIR)/gui.c $(SRC_DIR)/phone.c \
          $(SRC_DIR)/phone_ui.c $(SRC_DIR)/app_manager.c \
          apps/calculator.c apps/notes.c apps/apps.c
# Diğer uygulama kaynak dosyalarını da ekleyin

# Add optimization and debug flags
CFLAGS += -O2 -g -fPIC
LDFLAGS += -rdynamic

all: check-deps $(BUILD_DIR)/fusion_os

check-deps:
	@pkg-config --exists gtk+-3.0 || (echo "Installing GTK3 development files..." && sudo apt-get install -y libgtk-3-dev)

$(BUILD_DIR)/fusion_os: $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: check-deps $(BUILD_DIR)/fusion_os
	@echo "Running FusionOS tests..."
	./$(BUILD_DIR)/fusion_os

install-deps:
	sudo apt-get update
	sudo apt-get install -y \
		build-essential \
		libgtk-3-dev \
		pkg-config

clean:
	rm -rf $(BUILD_DIR)

RESOURCES = $(SRC_DIR)/style.css
INSTALL_DIR = $(BUILD_DIR)/resources

install: $(BUILD_DIR)/fusion_os
	mkdir -p $(INSTALL_DIR)
	cp $(RESOURCES) $(INSTALL_DIR)/

# Add new targets
.PHONY: debug release clean install

debug: CFLAGS += -DDEBUG -ggdb
debug: all

release: CFLAGS += -DNDEBUG
release: all
