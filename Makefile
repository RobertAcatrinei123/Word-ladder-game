# Compiler and linker
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I include

# Qt configuration
override QT_DIR = /opt/homebrew/opt/qt@6
CXXFLAGS += -I $(QT_DIR)/include -I $(QT_DIR)/include/QtCore -I $(QT_DIR)/include/QtGui -I $(QT_DIR)/include/QtWidgets -D QT_CORE_LIB -D QT_GUI_LIB -D QT_WIDGETS_LIB -fPIC
LDFLAGS = -F$(QT_DIR)/lib # Use -F for framework search path
LIBS = -framework QtCore -framework QtGui -framework QtWidgets # Link frameworks

TARGET = app
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Rule to link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Rule to compile source files into object files
obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the object directory
obj:
	@mkdir -p $@

clean:
	rm -f $(TARGET)
	rm -rf obj

leaks: $(TARGET) # Ensure target is built before leaking
	leaks -atExit -- ./$(TARGET)

run: $(TARGET) # Ensure target is built before running
	./$(TARGET)	

.PHONY: all clean leaks run