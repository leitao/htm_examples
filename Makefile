GCC=gcc
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
	$(GCC) -g -o nop nop.c
	$(GCC) -g -o illegal illegal.c
	$(GCC) -g -o illegal_ntm illegal_ntm.c
	$(GCC) -g -o thread thread.c -lpthread
	$(GCC) -g -o badstack badstack.c
	$(GCC) -g -o treclaim treclaim.c
	$(GCC) -g -o signal signal.c
	$(GCC) -g -o nested_signal nested_signal.c
	

clean:
	rm tend tabort ttrap ttrap2 ttrap3 spr tloop abno
	rm syscall syscall2 a.out forever nonhtmtrap notend 
	rm sleep treclaim spr_preservation
