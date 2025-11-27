# Makefile

# Namn på det körbara programmet
EXECUTABLE = minesweeper

# Kompilator
CC = g++

# Kompilatorflaggor
CFLAGS = -Wall -g -std=c++17

# Källfiler
SOURCES = main.cpp Game.cpp MinesweeperBoard.cpp Cell.cpp

# Katalog för objektfiler
OBJDIR = build

# Skapa motsvarande .o-filnamn i OBJDIR
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

# Var den färdiga binären hamnar
TARGET = $(OBJDIR)/$(EXECUTABLE)

.PHONY: all
all: $(TARGET)

# Länka ihop alla objektfiler till ett körbart program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Bygg regel för varje .cpp -> .o in i build/
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Skapa build/-mappen om den inte finns
$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
