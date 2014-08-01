CC=g++
INCDIR=include
CFLAGS=-c -Wall -std=c++1y -I$(INCDIR)/
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lGLEW -lmodplug
ifdef DEBUG
	CFLAGS += -O0 -g
else
	CFLAGS += -O3
endif
FILES=main.cpp game.cpp modstream.cpp spritefont.cpp spritetext.cpp
OBJDIR=build
SRCDIR=src
SOURCES=$(addprefix $(SRCDIR)/,$(FILES))
OBJECTS=$(addprefix $(OBJDIR)/,$(FILES:.cpp=.o))
ifdef DEBUG
	EXEDIR=x64/Debug
else
	EXEDIR=x64/Release
endif
EXECUTABLE=gbjam_nix

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -o $@ $<

$(EXECUTABLE): $(OBJECTS)
	@echo Output to: $(EXEDIR)
	@$(CC) $(LDFLAGS) -o $(EXEDIR)/$@ $^

.PHONY: clean
clean:
	@echo Cleaned $(OBJDIR) and $(EXEDIR)/$(EXECUTABLE)
	@rm -rf $(OBJDIR)/*.o $(EXEDIR)/$(EXECUTABLE)

