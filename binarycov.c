/*
 *  Homework 2
 *  C Programming
 *  Created on: Jan 15, 2016
 *      Author: Kevin Nguyen
 */


#include <stdio.h>
int main(void) {
 FILE*picFile;
 FILE*smallOutFile;
 FILE*bigOutFile;
 char twoBytes[2];
 int fileSize,width,height=0;
 int bigfilesize,bigwidth,bigheight,rows,columns,bigpixelsize=0;
 char headData[12];
 char secondheadData[28];
 int smallsize,smallpixsize,smallwidth,smallheight=0;
 
 picFile = fopen("test1.bmp","rb"); //read through any test.bmp file
 bigOutFile = fopen("big.bmp","wb");
 smallOutFile = fopen("small.bmp","wb");
 
 fread(twoBytes,1,2,picFile); //read through original .bmp pic and scan info.
 fread(&fileSize,1,4,picFile);
 fread(headData,1,12,picFile);
 fread(&width,1,4,picFile);
 fread(&height,1,4,picFile);
 fread(secondheadData,1,28,picFile);
 char Pixel[height][width*3];
 fread(Pixel,1,fileSize-54,picFile);
 
 char Small[height/2][(width/2)*3]; //construct a small .bmp picture with its specs.
 smallsize=fileSize/4;
 smallpixsize=(fileSize-54)/4;
 smallwidth=width/2;
 smallheight=height/2;
 char BIG[height*2][width*2*3]; //construct a big .bmp picture with its specs.
 bigfilesize=fileSize*4;
 bigpixelsize=(fileSize-54)*4;
 bigwidth=width*2;
 bigheight=height*2;
 
 for(rows=0;rows<height;rows+=2){ 
  for(columns=0;columns<width*3;columns+=6){
   Small[rows/2][columns/2]=Pixel[rows][columns];
   Small[rows/2][(columns/2)+1]=Pixel[rows][columns+1];
   Small[rows/2][(columns/2)+2]=Pixel[rows][columns+2];
  }
 }
 for(rows=0;rows<height;rows++){
  for(columns=0;columns<width*3;columns+=3){
   BIG[rows*2][columns*2]=Pixel[rows][columns];
   BIG[rows*2][(columns*2)+1]=Pixel[rows][columns+1];
   BIG[rows*2][(columns*2)+2]=Pixel[rows][columns+2];
   BIG[rows*2][(columns*2)+3]=Pixel[rows][columns];
   BIG[rows*2][(columns*2)+4]=Pixel[rows][columns+1];
   BIG[rows*2][(columns*2)+5]=Pixel[rows][columns+2];
   BIG[(rows*2)+1][columns*2]=Pixel[rows][columns];
   BIG[(rows*2)+1][(columns*2)+1]=Pixel[rows][columns+1];
   BIG[(rows*2)+1][(columns*2)+2]=Pixel[rows][columns+2];
   BIG[(rows*2)+1][(columns*2)+3]=Pixel[rows][columns];
   BIG[(rows*2)+1][(columns*2)+4]=Pixel[rows][columns+1];
   BIG[(rows*2)+1][(columns*2)+5]=Pixel[rows][columns+2];
  }
 }
 fwrite(twoBytes,1,2,smallOutFile); //write file out to small .bmp pic.
 fwrite(&smallsize,1,4,smallOutFile);
 fwrite(headData,1,12,smallOutFile);
 fwrite(&smallwidth,1,4,smallOutFile);
 fwrite(&smallheight,1,4,smallOutFile);
 fwrite(secondheadData,1,28,smallOutFile);
 fwrite(Small,1,smallpixsize,smallOutFile);
 fwrite(twoBytes,1,2,bigOutFile); //write file out to big .bmp pic.
 fwrite(&bigfilesize,1,4,bigOutFile);
 fwrite(headData,1,12,bigOutFile);
 fwrite(&bigwidth,1,4,bigOutFile);
 fwrite(&bigheight,1,4,bigOutFile);
 fwrite(secondheadData,1,28,bigOutFile);
 fwrite(BIG,1,bigpixelsize,bigOutFile);
 fclose(picFile); //close necessary files used.
 fclose(bigOutFile);
 fclose(smallOutFile);
 
 return 0;
}
