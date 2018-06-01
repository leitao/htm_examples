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
	

check:
	./tend
	./tabort
	./spr
	./tloop
	./abno
	./ttrap
	./ttrap2
	./ttrap3
	./syscall
	./syscall2
clean:
	rm -fr tend tabort ttrap ttrap2 ttrap3 spr tloop abno syscall syscall2
