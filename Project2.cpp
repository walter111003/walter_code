// matrix-multiplication <Project2.cpp>
// ECE 312 Project 2 submission by
// <Your Name Here>
// <Your EID>
// Slip days used: <0>
// Fall 2023

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {
   // https://en.wikipedia.org/wiki/Row-_and_column-major_order
  //const uint32_t b_rows = a_cols ; 
 
  double sumofC = 0 ; 


   for(int i = 0; i<a_rows; i++) {
    for(int j =0; j<b_cols; j++){
        for(int k = 0; k<a_cols; k++){

            sumofC += a[(i*a_cols) + k] * b[(k* b_cols) + j];
           
            
        }

        c[i*b_cols + j] = sumofC; 
        sumofC = 0; 

    }


    }
    

     
    
} 




  

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols

        ) 
        {
    const uint32_t b_rows = a_cols ; 
            
            

    // a = (double**) malloc(a_rows * sizeof(double*)); 
    // b = (double**) malloc(b_rows *sizeof(double*)); 
double** c = (double**) malloc(a_rows * sizeof(double*)); 

if(c == NULL){
    return NULL; 
}



for(int i = 0; i< a_rows; i++){
c[i]= (double*) malloc(b_cols*sizeof(double)); 
    if(c[i] == NULL){
        for(int k = 0; k<a_rows; k++){
            free(c[k]);


        }
        free(c);
        return NULL; 
    }

}


// for( uint32_t i = 0; i< a_rows; i++){
//     a[i]= (double*) malloc(a_cols*sizeof(double));

// }

// for( uint32_t i = 0; i < b_rows; i++ ){
//     b[i]= (double*) malloc(b_cols*sizeof(double)); 

// }


for(int i =0; i<a_rows; i++){

    for(int j = 0; j< b_cols; j++){
        c[i][j] = 0;
        for(int k = 0; k<b_rows; k++){

            c[i][j] += a[i][k]*b[k][j];
        }


    }
}






    





return c;
}




// https://en.wikipedia.org/wiki/Matrix_(mathematics)#Submatrix
double** createSubMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols,
		 const uint32_t row_x, 
		 const uint32_t col_y) {

        double** c = (double**) malloc((a_rows-1) * sizeof(double*)); 

        if(c == NULL){
            return NULL ; 
        }
   
        for(int i =0; i<a_rows-1; i++){
            c[i] = (double*)malloc((a_cols-1)*sizeof(double));
            if(c[i] == NULL){
                for(int k = 0; k<i; k++){
                    free(c[i]);
                }
                free(c);
                return NULL; 
        }
  }
int y = 0; 
        for(int i = 0; i<a_rows; i++){
            if(i != row_x){
                int b = 0; 
                for(int j = 0; j<a_cols; j++){
                    if(j != col_y){
                        c[y][b] = a[i][j];
                        b++; 
                    }
                }
                y++; 
            }
          
        }
    return c; 




}




