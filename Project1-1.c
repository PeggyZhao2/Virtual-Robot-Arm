/*	               
Name: Peiqi(Peggy) Zhao
Date: 10/1/2019

This program loads a pile and finds the color of the topmost piece. */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
   int	             PileInts[1024];
   int	             NumInts, TopColor=0;
   int  Load_Mem(char *, int *);
   // This allows you to access the pixels (individual bytes)
   // as byte array accesses (e.g., Pile[25] gives pixel 25):
   char *Pile = (char *)PileInts;

   if (argc != 2) {
     printf("usage: ./P1-1 valuefile\n");
     exit(1);
   }
   NumInts = Load_Mem(argv[1], PileInts);
   if (NumInts != 1024) {
      printf("valuefiles must contain 1024 entries\n");
      exit(1);
   }

   if (DEBUG){
     printf("Pile[0] is Pixel 0: 0x%02x\n", Pile[0]);
     printf("Pile[107] is Pixel 107: 0x%02x\n", Pile[107]);
   }

   /* Your program goes here */

   int pixel;
   int pixel_next;
   int pixel_next_next;
   int upper_pixel;
   int lower_pixel;
   int left_pixel;
   int right_pixel;
   int index;
   //0: not top
   //1: top
   int top_possible[8] = {1, 1, 1, 1, 1, 1, 1, 1};

   //*******if the pixel is already marked 0, skip it**********////
   //outter loop through rows 
   for (int row = 0; row < 64; row++) {
      //inner loop through columns
      for (int col = 0; col < 64; col++) {
        //get the current pixel from array
        index = row * 64 + col;
        pixel = Pile[index];//pixel is color from 0 to 7
        //check if the pixel is already marked 0 or not, if marked 0, skip
        //if the pixel is not black(0)
        //if the next pixel is not black(0) either and the next pixel is not the same as current pixel
        //if the current pixel and the third pixel are SAME
        //****check the upper and lower pixel of third pixel****, if any of those two are the SAME as third pixel
        //*****the bottom pixel is pixel_next
        //then change possible value to 0

        //pixel_int = pixel;
        if ((top_possible[pixel] != 0) && (pixel != 0)) {
          pixel_next = Pile[index + 1];
          //if next pixel is not black(0) either, and current and next pixel aren't the SAME
          if ((pixel_next != 0) && pixel != pixel_next) {
            pixel_next_next = Pile[index + 2];
            //check 1st and 3rd, if same
            if (pixel == pixel_next_next) {
              //check the upper and lower pixel of third pixel
              upper_pixel = Pile[(row - 1) * 64 + col + 2];
              lower_pixel = Pile[(row + 1) * 64 + col + 2];
              if ((upper_pixel == pixel_next_next) || (lower_pixel == pixel_next_next)) {
                top_possible[pixel_next] = 0;//pixel next is 0
              } else {
                top_possible[pixel] = 0;
              }
            }

          } 
        }
      }
   }

   //outter loop for columns
   for (int col = 0; col < 64; col++) {
    //innter loop through rows 
    for (int row = 0; row < 64; row++) {
      index = col * 64 + row;
      pixel = Pile[index];
      //if pixel is still possible to be on the top AND pixel is not black(0)
      if ((top_possible[pixel] == 1) && (pixel != 0)) {
        pixel_next = Pile[index + 1];
        //if next pixel is not black(0) either, and current and next pixel aren't the SAME
        if ((pixel_next != 0) && (pixel != pixel_next)) {
          //if the first and third pixel are the same
          if (pixel == pixel_next_next) {
            //if left or right pixel of the 3rd is the same as 3rd, pixel_next bottom
            left_pixel = Pile[index - 1];
            right_pixel = Pile[index + 1];
            if ((left_pixel == pixel_next_next) || (right_pixel == pixel_next_next)) {
              top_possible[pixel_next] = 0;
            } else {
              top_possible[pixel] = 0;
            }
          }
        }
      }
      
    }
   }

   //loop through top_possible to find 1
   int i = 1;
   while (top_possible[i] != 1 && i < 8) {
    i++;
   }
   TopColor = i;

   //printf("array### %d\n", TopColor);
   printf("The topmost part color is: %d\n", TopColor);
   exit(0);
}

/* This routine loads in up to 1024 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 1024; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}
