# Nom de l'exécutable
EXEC = test_gauss

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Fichiers sources
SRCS = test_gauss.c matrice.c gauss.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut : tout compiler
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(EXEC)
