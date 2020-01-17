#######################
# Makefile
#
# using static: 
#  1:(same with dynamic ):
# 	LIBB = -L/home/../ -lxxx  (use libxxx.a)
# 	main: main.o
#    	gcc $< -o $@  $(LIBB)  # must put back!!! 
#  2:another method : 
# 	 $(CC) $(CFLAGS) $^  -o $@  /lib/libtest.a

# target
TARGET := main

# compile and lib parameter
CC      := gcc
CFLAGS  := 
CXXFLAGS:= 
LDFLAGS := -L../ -la -lb 
DEFINES :=
INCLUDE := -I..

SRCS = $(TARGET:%=%.c) # source files
OBJS = $(SRCS:.c=.o)

# link
$(TARGET): $(OBJS)
	$(CC) -o $@ $^  $(LDFLAGS) 

#compile
%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< 


clean:
	rm -fr *.o
	rm -fr $(TARGET)

#to use library , you must ;
#export LD_LIBRARY_PATH=../$LD_LIBRARY_PATH
