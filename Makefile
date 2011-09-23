all:
	make -C lx
	make -C widgets
	make -C test

clean:
	make -C lx clean
	make -C widgets clean
	make -C test clean


.PHONY: all clean
