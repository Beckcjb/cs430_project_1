// Owner: Charles Beck
// Date: 9/7/16
// Class: CS 430

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RGBPixel{										// Data structure for pixel data in image file.
	unsigned char r, g, b;										 
}RGBPixel;

typedef struct{													// Structure for image data.
	int x, y;
	RGBPixel *data;
} Image;

char type[16]; 													// Allocate memory for responses.
int width;
int height;
double image_data[];											// Array for ascii data and binary data.
char* fileName;													// File name value.

void p3_to_p6(){
	fprintf("p3 to p6 converter:\n");	
	fprintf("Enter in the name of file with extention (input.ppm): ")	// Ask what file they want converted.
	fscanf = ("%s", fileName);									// Scan in answer.
	int i, j, count;
	double buffer[16];
	FILE* fh = fopen(fileName, "r");

	if (!fh) {
		fprintf(stderr, "File not able to open, may not exist.\n", fileName);
		return(1);
		}
																// Image data.
	if (!fgets(buff, sizeof(buff), fp)) {
	  perror(fileName);
	  exit(1);
	}
		
	if (buffer[0] != 'P' || buffer[1] != '3') {					// Check if file is P3.
		fprintf(stderr, "Error: Usage, P3 files only\n");
		exit(1);
	}
																// Alloc memory form image.
    img = (Image *)malloc(sizeof(Image));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }
    while (fgetc(fp) != '\n') ;
																// Memory allocation for pixel data.
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {													// See if image data exists.
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

}

void p6_to_p3(){
	fprintf("p6 to p3 converter:\n");	
	fprintf("Enter in the name of file with extention (input.ppm): ")// Ask what file they want converted.
	fscanf = ("%s", fileName);									// Scan in answer.
	int i, j, count, rgb_color;
	Image *img;
	double buffer[16];											// Buffer for header information.
	FILE* fh = fopen(fileName, "r");
	if (!fh) {
			fprintf(stderr, "File not able to open, may not exist.\n", fileName);
			return(1);
			}
	// Image data
	if (!fgets(buffer, sizeof(buffer), fp)) {
	  perror(fileName);
	  exit(1);
	}
	if (buffer[0] != 'P' || buffer[1] != '6') {					// Check to see is file is P6.
		fprintf(stderr, "Error: Usage, P6 files only\n");
		exit(1);
		
	}
																// Alloc memory form image.
    img = (Image *)malloc(sizeof(Image));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }
																// Read image size information.
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Error: Image size not valid)\n", fileName);
         exit(1);
    }
																// Read image data.
    if (fread(img->data, 3 * img->x, img->y, fh) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", fileName);
         exit(1);
    }
	else if(fread(img->data, 3 * img->x, img->y, fh) == img->y){
		
	}

	
}

int main(int argc, char *argv[]){
	fprintf("p3 and p6 converter:\n");	
	fprintf("Enter in the type of File you need converted: ")	// Ask what file type they want converted.
	fscanf = ("%s", type);										// Scan in answer.
	if (type == "p3"){											// If selection is p3 then go to p3_to_p6 converter method.
		p3_to_p6();
		}
	if (type == "p6"){											// If selection is p6 then go to p6_to_p3 converter method.
		p6_to_p3();
		}
	if(type != "p3" || type != "p6"){							// If selection is neither then send error and description.
		printf("Error: Usage, only P3 or P6 file conversion.");
		return(1);
		}
}
