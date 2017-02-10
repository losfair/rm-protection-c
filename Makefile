CFLAGS := -O3

all:
	make build
	make release

build: protect rm-p

release:
	rm -f build/build.tar.xz | true
	tar c build | xz -9 > build.tar.xz
	mv build.tar.xz build/

clean:
	rm -f *.o
	rm -rf build

protect: protect.o common.o build/static build/dynamic
	$(CC) $(CFLAGS) -o build/static/protect --static protect.o common.o
	$(CC) $(CFLAGS) -o build/dynamic/protect protect.o common.o
	strip build/static/protect build/dynamic/protect

rm-p: rm_p.o common.o build/static build/dynamic
	$(CC) $(CFLAGS) -o build/static/rm-p --static rm_p.o common.o
	$(CC) $(CFLAGS) -o build/dynamic/rm-p rm_p.o common.o
	strip build/static/rm-p build/dynamic/rm-p

build/dynamic:
	mkdir -p build/dynamic

build/static:
	mkdir -p build/static
