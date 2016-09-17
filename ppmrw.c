// Owner: Charles Beck
// Date: 9/16/16
// Class: CS 430
// 
// Project 1: PPM File Read Write
//
// ==============================================================================================
// This program reads in four string arguments from the command line and
// and reads ppm file data and out puts a specified ppm file type by the user.
 
// Usage in the command line:
//  ppmrw 3/6(intended output type) input.ppm output.ppm
//		
//		Before the string arguments are stored the program will error check to see if
// the input and output files are the correct type and the desired file type is correct as well.
// After the tests, main will read the header of the file and get the type then it will pass on
// the file name and output file type to the correct store method be it ascii or raw data.
// The store methods will error check to see if the file exists or hs any data at all. Next 
// based off of the output type argument entered by the user the program will send off the sorted 
// image data and file output name to the write method specified. Then the program will either 
// write a P3 file or a P6 based off of the users requests. Error checking is used through out to 
// ensure the correct proccesses occur.  
// ===============================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============= DATA STRUCTRES =====================================================================
typedef struct RGBPixel{						// Data structure for pixel data in image file.
	unsigned char r, g, b;										 
}RGBPixel;

typedef struct Image {							// Structure for image data.
	int w, h;
	RGBPixel *data;
} Image;

#define rgb_color 255							// We are not using ppm files that obtain an alpha channel 
												// 		so we can define rgb color depth as 255
												
//============== GLOBAL VARIABLES ===================================================================
char* type; 									// Allocate memory for responses.
int width;
int height;										
char* fileNameIn;	
char* fileNameOut;	
char* buffer[24];
int fileHeader[2];			
FILE* fi;
FILE* fo;										// File name value.
						// pointer to Image data
//============= WRITE METHODS: P6 ========================================================================
												// void write_P6(char *fileName, Image *img)
void write_P6(char* fileNameOut, Image* imaged)
{
	printf("Stored Data, Now writing\n");
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
	int i, j;
	  for (i = 0; i < imaged->h; ++i){
		for (j = 0; j < imaged->w; ++j){
				fwrite(imaged->data, 1, 3, fo);
	  }
	  }
    fclose(fo);
	printf("File write complete...");
}
//============= WRITE METHODS: P3 ========================================================================
void write_P3(char* fileNameOut, Image* imaged)
{
	printf("Stored Data, Now writing\n");
	width = imaged->w;
	height = imaged->h;

    FILE *fo = fopen(fileNameOut, "w");				//open file for output
												
													//write the header file
													//image format
    fprintf(fo, "P3\n");
	printf("P3\n");
													//image size
    fprintf(fo, "%d     %d\n",imaged->w,imaged->h);
	printf("%c %c\n",imaged->w,imaged->h);

													// write pixel data
   
  int i, j;
 

  for (i = 0; i < imaged->h; ++i){
    for (j = 0; j < imaged->w; ++j){
			fwrite(imaged->data, 1, 3, fo);
	}
  }
	fclose(fo);


    
	printf("File write complete...");
}
// ========== READ METHODS: ASCII ==================================================
void readStoreASCII(char* fileNameIn, char* fileNameOut, char* type){	
		printf("Storing Data.\n");
	int i, j, count, comments, d ,endOfHead, headerLength ;
	Image *imaged;
	width = imaged->w;
	height = imaged->h;
	
	FILE* fi = fopen(fileNameIn, "r");				// open file for reading
	printf("opened file\n");
	if (fi == NULL) {								// if file does not exist send error
		printf("Error: Could not open file\n");
		exit(1);
	}
	
	
	int g = fgetc(fi);								// get header file type information
	for(i = 0 ; i<2; i++){
		g = fgetc(fi);
		fileHeader[i] = g;
		printf("%c\n", g);
		
	}
	if (fileHeader[0] != '3'){			// Check if file is P3 or P6.
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
	int temp;													// Read file data
	for(i = 0 ; i < height; i++ ){
		for(j = 0; j < width; j ++){
			printf("Reading File, placing pixels\n");
			fscanf(fi, "%d", &temp);
			imaged->data[i*width*3+3*j].r = temp;
			
			fscanf(fi, "%d", &temp);
			imaged->data[i*width*3+3*j+1].g = temp;
			
			fscanf(fi, "%d", &temp);
			imaged->data[i*width*3+3*j+2].b = temp;
		}
	}
	
	

	int types = atoi(type);
	int o = fgetc(fi);
	while(getc(fi) != EOF){
		o = fgetc(fi);
		
	if (types == 3){
		printf(" here ");
		fclose(fi);	// Close file
		write_P3(fileNameOut, imaged);						// if the number selected as output is a 3 go to write P3
		break; 
	}
	if (types == 6){
		fclose(fi);	// Close file
		write_P6(fileNameOut, imaged);						// if the number selected as output is a 6 go to write P6
		break; 
	}}
	
}
// ================ READ METHODS: RAW =============================================================
void readStoreRAW(char* fileNameIn, char* fileNameOut, char* type){	
	printf("Storing Data.\n");
	int i, j, count, comments, d ,endOfHead, headerLength, n;
	
	Image *imaged;
	
	width = imaged->w;
	height = imaged->h;
	
	FILE* fi = fopen(fileNameIn, "rb");
	printf("opened file\n");
	if (fi == NULL) {								// if file does not exist send error
		printf("Error: Could not open file\n");
		exit(1);
	}
	
	for (i = 0; i < 2; i++){									// File type p3 or p6
		d = fgetc(fi);
		fileHeader[i] = d;
		}	

	if (fileHeader[0] != 6){
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
																				//read image size information
    if (fscanf(fi,"%d %d", &width, &height) != 2) {
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
  	int temp,red, green , blue;													// Read file data
	for(i = 0 ; i < height; i++ ){
		for(j = 0; j < width; j ++){
			printf("Reading File, placing pixels\n");
			
			red = imaged->data[i*width*3+3*j].r;
			fread(&red, 1, 1, fi);
			
			green = imaged->data[i*width*3+3*j+1].g;
			fread(&green, 1, 1, fi);
			
			blue = imaged->data[i*width*3+3*j+2].b;
			fread(&blue, 1, 1, fi);
		}
	}
	
	int types = atoi(type);
	int o = fgetc(fi);
	while(getc(fi) != EOF){
		o = fgetc(fi);
		
	if (types == 3){
		printf(" here ");
		fclose(fi);	// Close file
		write_P3(fileNameOut, imaged);						// if the number selected as output is a 3 go to write P3
		break; 
	}
	if (types == 6){
		fclose(fi);	// Close file
		write_P6(fileNameOut, imaged);						// if the number selected as output is a 6 go to write P6
		break; 
	}}

}



//============================ MAIN =================================================================================
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
		if(strstr(type,  "3" ) == NULL || strstr(type, "6")){						// Check if file is in .ppm format
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

		}
	fclose(fi);
	if (fileHeader[1] == '3'){		
																// If input file is p3 go to store data in ascii
		readStoreASCII(fileNameIn, fileNameOut, type);
		}
	else if (fileHeader[1] == '6'){								// If input file is p6 go to store data in RAW
		readStoreRAW(fileNameIn, fileNameOut, type);
		}	



}
