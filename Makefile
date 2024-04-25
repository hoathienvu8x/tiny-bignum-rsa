CC = gcc
CFLAGS = -Wall -std=gnu99 -Wextra -Werror -pedantic
LDFLAGS = -I. -ldl -lpthread -lm
ifeq ($(build),release)
	CFLAGS += -O3
	LDFLAGS += -DNDEBUG=1
else
	CFLAGS = -Og -g
endif
RM = rm -rf

all: clean objects

objects:
	@mkdir -p objects

test: objects/bignum.o objects/rsa.o objects/test.o
	@$(CC) objects/rsa.o objects/bignum.o objects/test.o -o $@ $(LDFLAGS)
	@$(RM) objects/test.o

objects/%.o: %.c
	@$(CC) -c $(LDFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@$(RM) objects/* test
