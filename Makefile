all: b5i2iso.c
	gcc src/b5i2iso.c -o b5i2iso

clean:
	rm -f b5i2iso.c
	rm -f *~
