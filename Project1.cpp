// ECE 312 PA1
// Walter Contreras
// Wac944
// Slip days used: 0
// Spring 2023
// Santacruz


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



/*
   Wring a function to sort the words in 'words[]' and then print them to the console.
*/



char* array[101] = {NULL}; 
char* temp;
int counter = 0;
int length = 0;


void sort(char* array[], int count) {

   char* temp;


   for (int i = 0; i < count - 1; i++) {
       for (int j = i + 1; j < count; j++) {

           char* var3 = array[i];
           char* var4 = array[j];
           
           char derefi = *var3;
           
           char derefj = *var4;


        
           int k = 0;
           while (derefi != '\0' && derefj != '\0' && derefi == derefj) {
               derefi = var3[++k];
               derefj = var4[k];
           }


           if (derefi > derefj) {
               temp = array[i];
               array[i] = array[j];
               array[j] = temp;
           }
       }
   }
}


void printSortedWords(char words[]) {
   int j = 0;
   length = 0; 
   counter = 0; 


   while (words[length] != '\0') {
       length++;
   }


   for (int i = 0; i < length; i++) {
       
       if (words[i] != ' ' && words[i] != '\t' && words[i] != '\n') {
           temp = &words[i];
           array[counter] = temp;
           counter++;


          
           j = i;
           while (j < length && words[j] != ' ' && words[j] != '\t' && words[j] != '\n' && words[j] != '\0') {
               j++;
           }


           
           if (j < length) {
               words[j] = '\0';
           }


           i = j; 
       }
   }


   sort(array, counter);


   
   for (int i = 0; i < counter; i++) {
       printf("%s\n", array[i]);
   }
}









