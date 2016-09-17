# cs430_project_1
P3 and P6 ppm file converter.
 Owner: Charles Beck
 Date: 9/16/16
 Class: CS 430
 
 Project 1: PPM File Read Write

 This program reads in four string arguments from the command line and
and reads ppm file data and out puts a specified ppm file type by the user.
 
Usage in the command line:
  ppmrw 3/6(intended output type) input.ppm output.ppm
  
Before the string arguments are stored the program will error check to see if
 the input and output files are the correct type and the desired file type is correct as well.
 After the tests, main will read the header of the file and get the type then it will pass on
 the file name and output file type to the correct store method be it ascii or raw data.
 The store methods will error check to see if the file exists or hs any data at all. Next 
 based off of the output type argument entered by the user the program will send off the sorted 
 image data and file output name to the write method specified. Then the program will either 
 write a P3 file or a P6 based off of the users requests. Error checking is used through out to 
 ensure the correct proccesses occur.  
 
  
  As of right now the program can only store the data correctly and has an error when writing to the new file
  of either type of document.
