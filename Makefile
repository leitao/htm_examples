CC=gcc
CFLAGS=-lpthread

objects = tend tabort ttrap ttrap2 ttrap3 spr tloop abno syscall syscall2 syscall3 forever notend nonhtmtrap nop illegal illegal_ntm thread badstack treclaim signal nested_signal corrupt signal_htm signal_pthread

all: $(objects)


$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm $(objects)

check: $(objects)
	$(foreach var,$(objects),echo $(var); ./$(var);)
