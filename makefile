DETECTED_OS := $(shell uname -s)

# ---- Choose the day file to build ----
mission ?= X
MISSION_SRC := mission$(mission).cpp


BUILD_DIR := build
SRCS   := $(MISSION_SRC) $(wildcard plib/*.cpp)
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:.cpp=.o))
DEPS := $(OBJS:.o=.d)
TARGET := mission$(mission)

ifeq ($(DETECTED_OS),Darwin)
	CXX := clang++
	ARCHFLAGS := -march=native -mcpu=apple-m4
else 
	CXX := g++
endif

# ---- Flags ----
STD      := -std=c++23
WARN     := -Wall -Wextra
DEPFLAGS := -MMD -MP
BASE     := $(STD) $(WARN) $(DEPFLAGS)

# Default Debug build: make DEBUG=1
CXXFLAGS := $(BASE) -O0 -g -fno-omit-frame-pointer -DDEBUG $(ARCHFLAGS)

ifeq ($(RELEASE),1)
	# Optimized build (fast)
	CXXFLAGS := $(BASE) -O3 -ffast-math -DNDEBUG -DRELEASE $(ARCHFLAGS)
endif

# ---- Rules ----
.PHONY: all clean run gdb

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Launch GDB TUI for the selected day (forces DEBUG=1 for sane symbols)
gdb: DEBUG=1
gdb: $(TARGET)
	gdb -tui ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) mission?? mission?

# Include auto-generated dependencies
-include $(DEPS)
