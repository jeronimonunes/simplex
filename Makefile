all:
	cd bigint && $(MAKE)
	cd src && $(MAKE)

clean:
	cd bigint && $(MAKE) clean
	cd src && $(MAKE) clean
