# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#	-g    adds debugging information to the executable file
#	-Wall turns on most, but not all, compiler warnings
#	-c into and an object file (.o file)
CFLAGS  = -c -g -Wall --std=c++11

LDFLAGS =

# docs = https://www.gnu.org/software/make/manual/make.html
# some compilation flags = https://web.engr.oregonstate.edu/~rubinma/Mines_274/Content/Slides/05_compilation.pdf
# helper = http://www.opennet.ru/docs/RUS/gnumake/#Multi-config_multi-dirs
# the build target executable:
SRC_DIR = source
SOURCES = $(addsuffix .cpp, main parser lexer logger)
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

#SRCH_WILDCARDS = $(addsuffix /*.cpp,$(SRC_DIR))

EXECUTABLE = $(OBJ_DIR)/work.a
DATA = data/input.txt

.PHONY: all clean do run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

VPATH = $(SRC_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(addprefix -I,$(SRC_DIR)) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

do: all
	./$(EXECUTABLE) $(DATA)

run: all
