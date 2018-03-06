
objs := $(patsubst %c, %o, $(shell ls *.c))

CC := gcc

MODULE_NAME := mycrypt
MODULE_TYPE := 



$(MODULE_NAME)$(MODULE_TYPE):$(objs)
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.bin *_elf *.dis *.o

