#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<iostream>
#include <string>
using namespace std;
 //Compiler version g++ 6.3.


 int main () {

 int RowsA;
 int ColsA;
 int RowsB;
 int ColsB;
 int RowsPi;
 int ColsPi;



//Reading the dimension of the matrix A.

   cin >> RowsA;
   cin >> ColsA;


    //Reading the rest of the values of the matrix A

    double ** A=(double **) malloc(RowsA*sizeof(double *));

    for(int i = 0;i < RowsA;i++){
        A[i] = (double *) malloc(ColsA*sizeof(double));}

    for(int i = 0; i < RowsA; i++){
            for(int j = 0; j < ColsA;j++){
               cin >> A[i][j];
            }
    }

    //Reading the dimension of the matrix B and it's values

  cin >> RowsB;
  cin >> ColsB;

   double ** B =(double **) malloc(RowsB*sizeof(double *));

    for(int i = 0;i < RowsB;i++){
        B[i] = (double *) malloc(ColsB*sizeof(double));}

    for(int i = 0; i < RowsB; i++){
            for(int j = 0; j < ColsB;j++){
               cin >> B[i][j];
            }
    }


   //Reading the dimension of the vector Pi and it's values


    cin >> RowsPi;
    cin >> ColsPi;

    double * Pi =(double *) malloc(ColsPi*sizeof(double ));

    for(int j = 0; j < ColsPi;j++){
                cin >> Pi[j];
    }

    // Calulating the probabilities.
    
    double AB = 0;
    double PiAB = 0;
    double PiA = 0;

   double ** AxB =(double **) malloc(RowsA*sizeof(double *));
   for(int i = 0;i < RowsA;i++){
        AxB[i] = (double *) malloc(ColsB*sizeof(double));}
   double * PixA =(double *) malloc(ColsPi*sizeof(double ));
double* ProbabilityVector=(double*)malloc(ColsB*sizeof(double ));
    //PixA
    for(int j=0; j<ColsA; j++){
            for(int k=0; k< ColsA && k < RowsA; k++){
                PiA += Pi[k]*A[k][j];
            }
            PixA[j] = PiA;
            PiA = 0;
   }
    
   //AxB
  
   for(int i=0; i<RowsA; i++){
        for(int j=0; j<ColsB; j++){
            for(int k=0; k < ColsA && k < RowsB; k++){
                AB += A[i][k]*B[k][j];
            }
             AxB[i][j] = AB;
            AB = 0;
        }
    }
 


   //PIAxB

           for(int j=0; j<ColsB; j++){
            for(int k=0; k < ColsA && k < RowsB; k++){
                PiAB += PixA[k]*B[k][j];
            }
            ProbabilityVector[j] =PiAB;
            PiAB = 0;}

 
    cout << RowsPi << " " << ColsB<< " ";
    for(int i = 0; i < ColsB; i++){
     cout <<ProbabilityVector[i]<< " ";
    }


return 0;
           }
