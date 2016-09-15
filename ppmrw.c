 // Owner: Charles Beck
// Date: 9/7/16
// Class: CS 430
// ALLOCATE DATA FOR PIXEL STRUCTURE then just from the 
// information stored in the pixel buffer return either ascii data or the binary represention.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RGBPixel{										// Data structure for pixel data in image file.
	unsigned char r, g, b;										 
}RGBPixel;

typedef struct Image {											// Structure for image data.
	int x, y;
	RGBPixel *data;
} Image;

#define creator "CJB456"
#define rgb_color 255

int type; 														// Allocate memory for responses.
int width;
int height;														// Array for ascii data and binary data.
char* fileNameIn;	
char* fileNameOut;				
																// File name value.
Image *img;

																			// void write_P6(char *fileName, Image *img)
void write_P6(Image *img)
{
	width = img->y;
	height = img->x;
	int biit;
    FILE *fh = fopen("output.ppm", "w");
														//open file for outpu
    if (!fh) {
         printf("Unable to open file '%s'\n", fileNameOut);
         exit(1);
    }
																			//write the header file
																			//image format
    fprintf(fh, "P3\n");
	

																			//comments
    fprintf(fh, "# Created by %s\n",creator);
	
																			//image size
    fprintf(fh, "%d %d\n",img->x,img->y);

																			// rgb alpha
    fprintf(fh, "%d\n",rgb_color);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fh);
	
    fclose(fh);
}

void write_P3(Image *img)
{
	width = img->y;
	height = img->x;

    FILE *fh = fopen("output.ppm", "w");
														//open file for output
    if (!fh) {
         printf("Unable to open file '%s'\n", fileNameOut);
         exit(1);
    }
																			//write the header file
																			//image format
    fprintf(fh, "P6\n");
																			// add comments and creator information
    fprintf(fh, "# Created by %s\n",creator);
	
																			//image size
    fprintf(fh, "%d %d\n",img->x,img->y);

																			// rgb alpha
    fprintf(fh, "%d\n",rgb_color);

																			// write pixel data
    fwrite(img->data, 3 * img->x, img->y, fh);
	
    fclose(fh);
}

void read_file(){	
	printf("Enter in the name of file with extention you wish to store (#input.ppm): ");	// Ask what file they want converted.
	scanf ("%s", fileNameIn);										// Scan in answer.
	if(strstr(fileNameIn,  ".ppm" ) == NULL)
			printf("Error: usage ppmrw.c #input.ppm output.ppm\n");
	int i, j, count, comments, d ,endOfHead, headerLength;
	
	FILE* fh = fopen(fileNameIn, "r");
	endOfHead = getc(fh);
	
    while (getc(fh) != '\n') {
         endOfHead = getc(fh);
		 count++;												
		 if(getc(fh) == '\n'){
																// Break loop if the header reaches a new line
		 }														// PPM headers are formatted to have a new line at the end of the header
    }
	ungetc(endOfHead, fh);
	
	char fileHeader[count];
	if (!fh) {													// Check if file exists
		printf("File not able to open, may not exist.\n", fileNameIn);
		exit(1);
		}
	for (i = 0; i < count; i++){									// File type p3 or p6
		d = fgetc(fh);
		fileHeader[i] = d;
	}	
	if (fileHeader[2] == 3){
		write_P6(img);
	}
	if (fileHeader[2] == 6){
		write_P3(img);
	}

																//check for comments
     comments = getc(fh);
    while (comments == '#') {
    while (getc(fh) != '\n') ;
         comments = getc(fh);
    }
																//check for comments
     d = getc(fh);
    while (d == ' ') {
    while (getc(fh) != '\n') ;
         d = getc(fh);
    }
	if (fileHeader[0] != 'P' || fileHeader[1] != '3' ||fileHeader[1] != '6'){				// Check if file is P3 or P6.
		printf("Error: Usage, P3 and P6  files only\n");
		exit(1);
	}
	
	//read image size information
    if (fscanf(fh, "%d %d", &img->x, &img->y) != 2) {
        printf("Invalid image size (error loading '%s')\n", fileNameIn);
         exit(1);
    }
	
	while (fgetc(fh) != '\n') ;
																			//memory allocation for pixel data
    img->data = (RGBPixel*)malloc(img->x * img->y * sizeof(RGBPixel));
	
    if (!img) {
         printf("Unable to allocate memory\n");
         exit(1);
    }

																			//read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fh) != img->y) {
         printf("Error: Issue reading image '%s'\n", fileNameIn);
         exit(1);
	}
	
	fclose(fh);
}




int main(int argc, char *argv[]){
	printf("p3 and p6 converter:\n");	
	read_file();
	}
