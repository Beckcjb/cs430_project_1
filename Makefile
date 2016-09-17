

nmake:
	ppmrw.c
	gcc ppmrw.c -o ppmrw

	
clean:
	rm -rf output *~