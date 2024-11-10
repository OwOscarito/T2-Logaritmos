DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CPPFLAGS = -g -Og -DDEBUG
else
    CPPFLAGS = -O3 -Wall -Wextra -pthread -std=c++17 -DNDEBUG
endif

CXX = g++

BIN := main.exe
SRC := src/main.cpp

.PHONY: build run clean

$(BIN): build

build:
	$(CXX) $(CPPFLAGS) -o $(BIN) $(SRC)

run: $(BIN)
	$<

clean:
	$(RMDIR) $(OBJ)