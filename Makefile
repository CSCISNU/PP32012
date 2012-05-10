default: win

win: win.c
	gcc -Wall -o win

clean:
	rm -f *~ *.o win

