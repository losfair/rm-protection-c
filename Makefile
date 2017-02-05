CFLAGS := -O3

all:
	make protect
	make rm_p

protect: protect.o common.o
	$(CC) -o build/static/protect --static protect.o common.o
	$(CC) -o build/dynamic/protect protect.o common.o
	strip build/static/protect build/dynamic/protect

rm_p: rm_p.o
	$(CC) -o build/static/rm_p --static rm_p.o common.o
	$(CC) -o build/dynamic/rm_p rm_p.o common.o
	strip build/static/rm_p build/dynamic/rm_p

clean:
	rm *.o
	rm -r build && mkdir -p build/static build/dynamic
