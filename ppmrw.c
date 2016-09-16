// Owner: Charles Beck
// Date: 9/7/16
// Class: CS 430
// ALLOCATE DATA FOR PIXEL STRUCTURE then just from the 
// information stored in the pixel buffer return either ascii data or the binary represention.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct RGBPixel{						// Data structure for pixel data in image file.
	unsigned char r, g, b;										 
}RGBPixel;

typedef struct Image {							// Structure for image data.
	int w, h;
	RGBPixel *data;
} Image;

#define rgb_color 255							// We are not using ppm files that obtain an alpha channel 
												// 		so we can define rgb color depth as 255

char* type; 									// Allocate memory for responses.
int width;
int height;										
char* fileNameIn;	
char* fileNameOut;	
char* buffer[24];
int fileHeader[2];			
FILE* fi;
FILE* fo;										// File name value.
Image *imaged;									// pointer to Image data

												// void write_P6(char *fileName, Image *img)
void write_P6(char* fileNameOut, Image *imaged)
{
	width = imaged->w;
	height = imaged->h;
    FILE *fo = fopen(fileNameOut, "wb");
												//open file for outpu
    if (!fo) {
         fprintf(stderr, "Unable to open file '%s'\n", fileNameOut);
         exit(1);
    }
												//write the header file
												//image format
    fprintf(fo, "P3\n");
	printf("P3");
												//image size
    fprintf(fo, "%d %d\n",imaged->w,imaged->h);
	printf("%d %d\n",imaged->w,imaged->h);

												// rgb alpha
    fprintf(fo, "%d\n",rgb_color);
	printf("%d....\n",rgb_color);

    // pixel data
    fwrite(imaged->data, 3 * imaged->w, imaged->h, fo);
	
    fclose(fo);
	printf("File store complete");
}

void write_P3(char* fileNameOut, Image *imaged)
{
	width = imaged->w;
	height = imaged->h;

    FILE *fo = fopen(fileNameOut, "w");				//open file for output
												
													//write the header file
													//image format
    fprintf(fo, "P3\n");
	printf("P3");
													//image size
    fprintf(fo, "%d %d\n",imaged->w,imaged->h);
	printf("%d %d\n",imaged->w,imaged->h);

													// rgb alpha
    fprintf(fo, "%d\n",rgb_color);
	printf("%d....\n",rgb_color);
													// write pixel data
    fwrite(imaged->data, 3 * imaged->w, imaged->h, fo);
	
    fclose(fo);
	printf("File store complete");
}

void readStoreASCII(char* fileNameIn, char* fileNameOut, char* type){	
	printf("What happened here tooa?\n");
		
	int i, j, count, comments, d ,endOfHead, headerLength ;
	char reader;
	

	width = imaged->w;
	height = imaged->h;
	
	FILE* fi = fopen(fileNameIn, "r");
	
	fread(imaged->data, width, height, fi);
	int g = fgetc(fi);
	for(i = 0 ; i<2; i++){
		g = fgetc(fi);
		fileHeader[i] = g;
		printf("%c\n", g);
		
	}
	if (fileHeader[0] != 'P' || fileHeader[1] != '3'){			// Check if file is P3 or P6.
		fprintf(stderr, " ascii: Error: Usage, P3 and P6  files only\n");
		exit(1);
	}
	


	
	if (!fi) {													// Check if file existsn 
		fprintf(stderr, "File not able to open, may not exist.\n", fileNameIn);
		exit(1);
		}
																//check for comments
     comments = getc(fi);
    while (comments == '#') {
    while (getc(fi) != '\n') ;
         comments = getc(fi);
    }
																//check for whitespaces
     d = getc(fi);
    while (d == ' ') {
    while (getc(fi) != '\n') ;
         d = getc(fi);
    }

	
																//read image size information
    if (fscanf(fi, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", fileNameIn);
         exit(1);
    }
	
	while (fgetc(fi) != '\n') ;
																//memory allocation for pixel data
    imaged->data = (RGBPixel*)malloc(imaged->w * imaged->h * sizeof(RGBPixel));
    if (!imaged) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

																//read pixel data from file
	int pix;													// Read file data
	for(i = 0 ; i < height; i++ ){
		for(j = 0; j < width; j ++){
			fscanf(fi, "%d", &pix);
			imaged->data[i*width*3+3*j] = pix;
			
			fscanf(fi, "%d", &pix);
			imaged->data[i*width*3+3*j+1] = pix;
			
			fscanf(fi, "%d", &pix);
			imaged->data[i*width*3+3*j+2] = pix;
		}
	}
	
	fclose(fi);	// Close file
	printf("What happened here too?\n");
	if (type == "3"){
		write_P6(fileNameOut, imaged);   	// if the number selected as output is a 3 go to write P3
	}
	if (type == "6"){
		write_P3(fileNameOut, imaged);		// if the number selected as output is a 6 go to write P6
	}
	
}

void readStoreRAW(char* fileNameIn, char* fileNameOut, char* type){	
	printf("What happened here too?\n");
	int i, j, count, comments, d ,endOfHead, headerLength, n;
	char reader;
	
	width = imaged->w;
	height = imaged->h;
	
	FILE* fi = fopen(fileNameIn, "rb");
	
	fread(imaged->data, width, height, fi);
	for (i = 0; i < 2; i++){									// File type p3 or p6
		d = fgetc(fi);
		fileHeader[i] = d;
		}	

	if (fileHeader[1] != 6){
		fprintf(stderr, "Error: File must be P3 or P6\n");
	exit(1);}
	
	if (!fi) {													// Check if file exists
		fprintf(stderr, "raw: File not able to open, may not exist.\n", fileNameIn);
		exit(1);
		}
																//check for comments
     comments = getc(fi);
    while (comments == '#') {
    while (getc(fi) != '\n'){
		comments = getc(fi);}
    }
																//check for whitespaces
     d = getc(fi);
    while (d == ' ') {
    while (getc(fi) != '\n'){
		d = getc(fi);}
    }
	if (fileHeader[1] != '3' ||fileHeader[1] != '6'){						// Check if file is P3 or P6.
		fprintf(stderr, "raw: Error: Usage, P3 and P6  files only\n");
		exit(1);
	}
	
																			//read image size information
    if (fscanf(fi, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "raw: Invalid image size (error loading '%s')\n", fileNameIn);
         exit(1);
    }
	
	while (fgetc(fi) != '\n');
																			//memory allocation for pixel data
    imaged->data = (RGBPixel*)malloc(imaged->w * imaged->h * sizeof(RGBPixel));
	
    if (!imaged) {
         fprintf(stderr, "raw: Unable to allocate memory\n");
         exit(1);
    }

																			//read pixel data from file
    if (fread(imaged->data, 3 * imaged->w, imaged->h, fi) != imaged->h) {
         fprintf(stderr, "raw: Error: Issue reading image '%s'\n", fileNameIn);
         exit(1);
	}
	
	fclose(fi);	// Close file
	printf("What happened here too?\n");
	if (type == "3"){
		write_P6(fileNameOut, imaged);   	// if the number selected as output is a 3 go to write P3
	}
	if (type == "6"){
		write_P3(fileNameOut, imaged);		// if the number selected as output is a 6 go to write P6
	}

}




int main(int argc, char *argv[]){
	if (argc != 4) {
		fprintf(stderr, "Error: Usage ppmrw # input.ppm output.ppm");
		exit(1);
	}
	int d;
	fileNameOut = argv[3];
	fileNameIn = argv[2];
	type = argv[1];
	char* program = argv[0];
	if(strstr(program, "ppmrw") == NULL){							// Check if argument is valid
		fprintf(stderr, "Error: main Usage ppmrw 3(6) input.ppm output.ppm\n");
		exit(1);
	}
	if(strstr(fileNameIn,  ".ppm" ) == NULL){						// Check if file is in .ppm format
			fprintf(stderr, "Error: main usage ppmrw 3(6) input.ppm output.ppm\n");
			exit(1);
	}
	if(strstr(fileNameOut,  ".ppm" ) == NULL){						// Check if file is in .ppm format
			fprintf(stderr, "Error: main usage ppmrw 3(6) input.ppm output.ppm\n");
			exit(1);
	}
	FILE* fi = fopen(fileNameIn, "r");
	if (!fi) {													// Check if file exists
		fprintf(stderr, "main: File not able to open, %s may not exist.\n ", fileNameIn);
		exit(1);
		}
	for (int i = 0; i <2 ; i++){									// get File type p3 or p6
		d = fgetc(fi);
		fileHeader[i] = d;
		printf("%c", d);
		if (fileHeader[1] == 3){
			fclose(fi);		
			printf("WTF IS GOING ON!");				// If input file is p3 go to store data in ascii
			readStoreASCII(fileNameIn, fileNameOut, type);
			
		}
		if (fileHeader[1] == 6){		// If input file is p6 go to store data in RAW
			fclose(fi);
			readStoreRAW(fileNameIn, fileNameOut, type);
		}	
		
		}
		
		
	fclose(fi);

}
