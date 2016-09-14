

make3:
	ppmrw.c
	gcc ppmrw.c -o output

make6:
	ppmrw.c
	gcc ppmrw.c -o output
	
clean:
	rm -rf output *~