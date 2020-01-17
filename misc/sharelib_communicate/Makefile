#######################
# Makefile
# This is a example to generate *.so share library   
# static 
# 	ar r target.a a.o b.o
# dynamic:
# 	gcc -shared -o libfoo.so foo.o
#
# use static library:
# 1:(same with dynamic)
# 	LIBB = -L/home/.../ -lxxx   #(libxxx.a )
# 	main: main.o
#   	gcc  $(LIBB) $< -o $@
# 2: $(CC) $(CFLAGS) $^ -o $@  /lib/libxxx.a


CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command

TARGET = a 
TARGET_LIB = $(TARGET:%=lib%.so)#libb.so # target lib
LIBPATH = 

SRCS = $(TARGET:%=%.c) # source files
OBJS = $(SRCS:.c=.o)

all: ${TARGET_LIB}

# this can be omitted.  if not present, will, it can generate automtic gcc ${CFLAGS}
%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

$(TARGET_LIB): $(OBJS)
	@echo "===" $(TARGET_LIB) $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^ $(INCLUDE)

.PHONY: clean 
clean:
	rm *.o *.so



