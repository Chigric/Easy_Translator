# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#	-c into and an object file (.o file)
CFLAGS  = -c -g -Wall --std=c++11

LDFLAGS =

# the build target executable:
SOURCES = $(addsuffix .cpp, main parser)
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
EXECUTABLE = $(OBJ_DIR)/work.a
DATA = data/input.txt

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

do: all
	./$(EXECUTABLE) $(DATA)
