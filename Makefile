CC = gcc

CFLAGS = -Wall

EXE = todolist

SRCDIR = src
BUILDDIR = build
LIBDIR = lib

SRC := $(shell find $(SRCDIR) -type f -name *.c)
SRC += lib/sqlite3.c
SRCFOLDERS := $(shell find $(SRCDIR) -type d)

OBJ := $(SRC:%.c=$(BUILDDIR)/%.o)

# Super useful variables
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m

all: $(EXE)

$(EXE): $(OBJ)
	@echo "$(MAGENTA)Compiling $(CYAN)$(notdir $@)$(NC)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

$(LIBDIR):
	@echo "Downloading $(BLUE)sqlite3$(NC)"
	@wget -q -P $(LIBDIR)/ https://www.sqlite.org/2024/sqlite-amalgamation-3460000.zip
	@echo "$(MAGENTA)Extracting $(BLUE)sqlite3.c$(NC)"
	@unzip -p $(LIBDIR)/sqlite-amalgamation-3460000.zip sqlite-amalgamation-3460000/sqlite3.c > $(LIBDIR)/sqlite3.c
	@echo "$(MAGENTA)Extracting $(BLUE)sqlite3.h$(NC)"
	@unzip -p $(LIBDIR)/sqlite-amalgamation-3460000.zip sqlite-amalgamation-3460000/sqlite3.h > $(LIBDIR)/sqlite3.h
	@echo "$(RED)Clear temp files$(NC)"
	@rm $(LIBDIR)/sqlite-amalgamation-3460000.zip ||:

$(BUILDDIR):
	@echo "$(GREEN)Create $(BLUE)build$(GREEN) directory$(NC)"
	@mkdir -p $@/$(SRCDIR) $@/$(LIBDIR) $(SRCFOLDERS:%=$(BUILDDIR)/%)

# .o files
$(BUILDDIR)/%.o: %.c | $(BUILDDIR) $(LIBDIR)
	@echo "$(YELLOW)Compiling $(BLUE)$(notdir $@)$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(LIBDIR)

clean:
	@echo "$(RED)Clean project$(NC)"
	@rm -fr $(BUILDDIR) $(EXE) ||: