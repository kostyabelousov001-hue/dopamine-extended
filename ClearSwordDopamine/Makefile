# ClearSword Library for Dopamine Integration
# Target: iPhone XS (A12) - iOS 18.7.3

CC = clang
CFLAGS = -arch arm64 -isysroot $(SDK_PATH) -miphoneos-version-min=15.0 \
         -I. -DDEBUG=1 -DLOGGING_ENABLED=1
LDFLAGS = -framework IOKit -framework Foundation -lSystem

# Source files
SRCS = poc.c utils.c socket.c surface.c phys_oob.c kmem.c krw.c free_thread.c
OBJS = $(SRCS:.c=.o)

# Library output
LIB_NAME = libClearSword.a

.PHONY: all clean test

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^
	@echo "Built $(LIB_NAME)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB_NAME) test.o
	$(CC) $(CFLAGS) -o clearsword_test $^ $(LDFLAGS)
	@echo "Built clearsword_test"

install: $(LIB_NAME)
	@echo "Copy to Dopamine project:"
	@echo "  cp $(LIB_NAME) /path/to/Dopamine/BaseBin/libjailbreak/"
	@echo "  cp clearsword_krw.h clearsword_krw.c /path/to/Dopamine/BaseBin/libjailbreak/"

clean:
	rm -f *.o $(LIB_NAME) clearsword_test
