OBJDIR = build
SRCDIR = src
INCDIR = include

CXX = g++
FLAGS=-std=c++20 -Wall -Wextra -I./$(INCDIR)

EXE = DadeNegar

FORMAT = clang-format -style=file -i

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
HEADERS := $(wildcard $(INCDIR)/*.hpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))


all: $(OBJDIR) $(EXE)

$(OBJDIR):
	@mkdir -p $@

$(EXE): $(OBJECTS)
	$(CXX) $(FLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(FLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

format:
	$(FORMAT) $(SOURCES) $(HEADERS)

clean:
	@rm -f $(OBJDIR)/*.o $(EXE)
	@rmdir $(OBJDIR)

.PHONY: all run format clean
