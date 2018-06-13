GCC=gcc5
all:
	$(GCC) -g -o tend tend.c
	$(GCC) -g -o tabort tabort.c
	$(GCC) -g -o ttrap ttrap.c
	$(GCC) -g -o ttrap2 ttrap2.c
	$(GCC) -g -o ttrap3 ttrap3.c
	$(GCC) -g -o spr spr.c
	$(GCC) -g -o tloop tloop.c
	$(GCC) -g -o abno abno.c
	$(GCC) -g -o syscall syscall.c
	$(GCC) -g -o syscall2 syscall2.c
	$(GCC) -g -o forever forever.c
	$(GCC) -g -o notend notend.c
	$(GCC) -g -o nonhtmtrap nonhtmtrap.c
	

clean:
	rm tend tabort ttrap ttrap2 ttrap3 spr tloop abno \
	syscall syscall2 a.out forever nonhtmtrap notend  \
	sleep treclaim spr_preservation
