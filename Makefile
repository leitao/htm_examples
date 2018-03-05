GCC=gcc5
all:
	$(GCC) -g -o tend tend.c
	$(GCC) -g -o tabort tabort.c
	$(GCC) -g -o ttrap ttrap.c
	$(GCC) -g -o spr spr.c

check:
	./tend
	./tabort

clean:
	rm -fr tend tabort ttrap spr
