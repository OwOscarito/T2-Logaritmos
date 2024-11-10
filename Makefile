DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CPPFLAGS = -g -Og -DDEBUG
else
    CPPFLAGS = -O1 -Wall -Wextra -Wl,--stack,4294967296 -std=c++17 -DNDEBUG
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