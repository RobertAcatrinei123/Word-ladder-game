CXX = clang++
CXXFLAGS = -std=c++20 -Wall -g -I include

TARGET = app
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f src/*.o

leaks:
	leaks -atExit -- ./$(TARGET)

run:
	./$(TARGET)	

.PHONY: all clean obj