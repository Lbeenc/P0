CXX := g++
CXXFLAGS := -Wall -Wextra -Wpedantic -std=c++17 -O2

OBJS := P0.o tree.o
BIN := P0

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

P0.o: P0.cpp node.h tree.h

tree.o: tree.cpp node.h tree.h

clean:
	rm -f $(OBJS) $(BIN) *.preorder *.inorder *.postorder

.PHONY: all clean
