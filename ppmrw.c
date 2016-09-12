// Owner: Charles Beck
// Date: 9/7/16
// Class: CS 430

#include <stdio.h>
#include <stdlib.h>


typedef struct Pixel {
  unsigned char  r, g, b;
} Pixel;


double file_array [];
int i, j;



void read_file(filename){

	for(i = 0 ;  ; i++){
		FILE* fh = fopen(filename, "r");
		return fgetc(fh);
	}	
	
	
}

int main(argv, char* argc[]){
	
}