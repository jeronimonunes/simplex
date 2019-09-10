all: bigint/bigint.o src/a.exe

bigint/bigint.o:
	$(MAKE) -C bigint $(MAKECMDGOALS)

src/a.exe:	
	$(MAKE) -C src $(MAKECMDGOALS)

clean:
	$(MAKE) -C bigint $(MAKECMDGOALS)
	$(MAKE) -C src $(MAKECMDGOALS)
