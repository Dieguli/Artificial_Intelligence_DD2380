#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<iostream>
#include <string>

using namespace std;


class Lambda{
    private:
        double **A;
        double **B;
        double *Pi;
        double SequenceProbability = 0;
        double **Alpha;
        int * seq; 
        int Observations; 
   
        int ColsA;
        int RowsA;
        int ColsB;
        int RowsB;
        int RowsPi;
        int ColsPi;
    
    public:
        Lambda();
        ~Lambda();
        void ReadData();
        void EmissionProbability();
        void AlphaPass();
        void Results();
};

Lambda::Lambda(){

    ReadData();

    Alpha =(double **) malloc(ColsB*sizeof(double *));

    for(int i = 0;i < ColsB;i++)
    Alpha[i] = (double *)malloc(Observations*sizeof(double));
   


}

Lambda::~Lambda(){
    free(A);
    free(B);
    free(Pi);
    free(Alpha);
    free(seq);
}

void Lambda::ReadData(){

    cin >> RowsA;
    cin >> ColsA;

    A =(double **) malloc(RowsA*sizeof(double *));

    for(int i = 0;i < RowsA;i++)
        A[i] = (double *) malloc(ColsA*sizeof(double));

    for(int i = 0; i < RowsA; i++){
            for(int j = 0; j < ColsA;j++){
                cin >> A[i][j];
            }
    }

    cin >> RowsB;
    cin >> ColsB;

    B =(double **) malloc(RowsB*sizeof(double *));

    for(int i = 0;i < RowsB;i++)
        B[i] = (double *) malloc(ColsB*sizeof(double));

    for(int i = 0; i < RowsB; i++){
            for(int j = 0; j < ColsB;j++){
                cin >> B[i][j];
            }
    }

    cin >> RowsPi;
    cin >> ColsPi;

    Pi =(double *) malloc(ColsPi*sizeof(double ));

    for(int j = 0; j < ColsPi;j++){
        cin >> Pi[j];
    }

    cin >> Observations;

    seq =(int *) malloc(Observations*sizeof(int ));

    for(int i = 0; i < Observations; i++){
        cin >> seq[i];
    }

    return;
}


void Lambda::AlphaPass(){
    //1)
    for( int i = 0; i < RowsB ; i++){
        Alpha[i][0] = Pi[i]*B[i][seq[0]];
    }
    //2
    for(int i = 0; i < Observations - 1 ; i++){
        for( int k= 0; k < ColsA ; k++){
            for(int m = 0; m < RowsA; m++ ){
                Alpha[k][i+1] += Alpha[m][i]*A[m][k];
            }
            Alpha[k][i+1] *= B[k][seq[i+1]];
        }
    }
    //3
    for( int i = 0; i < RowsB; i++){
        SequenceProbability += Alpha[i][Observations - 1];
    }
}

void Lambda::Results(){
    cout << SequenceProbability;
}


int main()
{
    Lambda Test;
    Test.AlphaPass();
    Test.Results();
    
    return 0;
}
