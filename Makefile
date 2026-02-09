# ========================
# Compiler
# ========================
CXX := g++

# ========================
# Directories
# ========================
SRC_DIR := src
GUI_DIR := gui
INC_DIR := include
OBJ_DIR := build/obj
BIN_DIR := build/bin

# ========================
# Qt flags
# ========================
QT_CFLAGS := $(shell pkg-config --cflags Qt5Widgets)
QT_LIBS   := $(shell pkg-config --libs Qt5Widgets)

# ========================
# Flags
# ========================
CXXFLAGS := -std=c++17 -Wall -Wextra -fPIC -I$(INC_DIR) $(QT_CFLAGS)

# ========================
# Target
# ========================
TARGET := $(BIN_DIR)/text_editor

# ========================
# Sources
# ========================
SRCS := \
	$(SRC_DIR)/gap_buffer.cpp \
	$(SRC_DIR)/text_buffer.cpp \
	$(SRC_DIR)/undo.cpp \
	$(GUI_DIR)/editor_widget.cpp \
	$(GUI_DIR)/main_qt.cpp

# ========================
# Objects
# ========================
OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# ========================
# Default
# ========================
all: $(TARGET)

# ========================
# Link
# ========================
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(QT_LIBS)

# ========================
# Compile
# ========================
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ========================
# Clean
# ========================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
