CFLAGS := -O3

all:
	make protect
	make rm-p
	make release

release:
	rm build/build.tar.xz | true
	tar c build | xz -9 > build.tar.xz
	mv build.tar.xz build/

clean:
	rm *.o
	rm -r build && mkdir -p build/static build/dynamic

protect: protect.o common.o
	$(CC) -o build/static/protect --static protect.o common.o
	$(CC) -o build/dynamic/protect protect.o common.o
	strip build/static/protect build/dynamic/protect

rm-p: rm_p.o
	$(CC) -o build/static/rm-p --static rm-p.o common.o
	$(CC) -o build/dynamic/rm-p rm-p.o common.o
	strip build/static/rm-p build/dynamic/rm-p
