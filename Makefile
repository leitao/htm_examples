all:
	gcc5 -g -o tend tend.c
	gcc5 -g -o tabort tabort.c
	gcc5 -g -o ttrap ttrap.c
	gcc5 -g -o spr spr.c

check:
	./tend
	./tabort

clean:
	rm -fr tend tabort ttrap spr
