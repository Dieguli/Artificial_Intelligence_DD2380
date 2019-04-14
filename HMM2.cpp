#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#define NO_RUTE -1
//HMM2
using namespace std;

class Lambda{
    private:
        double **A;
        double **B;
        double *Pi;
        double ** AxB;
        double * PixA;
        double * ProbabilityVector;
        double SecuenceProbability = 0;
        double **Alpha;
        double **Delta;
        int ** statesSeq;
        double *c;
        int * ProbableSeq;
        int * obs;
        int Observations;
        int ColsA;
        int RowsA;
        int ColsB;
        int RowsB;
        int ColsPi;
        int RowsPi;

    public:
        Lambda();
        ~Lambda();
        void Output();
        void ReadData();
        void ShowMatrix();
        void EmissionProbability();
        void ForwardAlg();
        void ViterbiAlg();
};

Lambda::Lambda(){       //Matrices allocation

    ReadData();

    AxB =(double **) malloc(RowsA*sizeof(double *));

    for(int i = 0;i < RowsA;i++)
        AxB[i] = (double *) malloc(ColsB*sizeof(double));

    PixA =(double *) malloc(ColsPi*sizeof(double ));

    ProbabilityVector =(double *) malloc(ColsB*sizeof(double ));

    Alpha =(double **) malloc(ColsB*sizeof(double *));

    for(int i = 0;i < ColsB;i++)
        Alpha[i] = (double *) malloc(Observations*sizeof(double));

    Delta =(double **) malloc(ColsB*sizeof(double *));

    for(int i = 0;i < ColsB;i++)
        Delta[i] = (double *) malloc(Observations*sizeof(double));

    statesSeq =(int **) malloc(ColsB*sizeof(int *));

    for(int i = 0;i < ColsB;i++)
        statesSeq[i] = (int *) malloc(Observations*sizeof(int));

    ProbableSeq = (int *) malloc(Observations*sizeof(int));

    c = (double *) malloc(Observations*sizeof(double));
}

Lambda::~Lambda(){
    free(A);
    free(B);
    free(Pi);
    free(AxB);
    free(ProbabilityVector);
    free(PixA);
    free(Alpha);
    free(obs);
    free(c);
}

void Lambda::ReadData(){
    //Allocate A and read data
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
    //Allocate B and read data
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

    //Allocate Pi and read data
    cin >> RowsPi;
    cin >> ColsPi;

    Pi =(double *) malloc(ColsPi*sizeof(double ));

    for(int j = 0; j < ColsPi;j++){
                cin >> Pi[j];
    }
    //Allocate and read observations
    cin >> Observations;

    obs =(int *) malloc(Observations*sizeof(int ));

    for(int i = 0; i < Observations; i++){
           cin >> obs[i];
    }

    return;
}

void Lambda::ShowMatrix(){      //Displays the matrices

        for(int i = 0; i < RowsA; i++){
            for(int j = 0; j < ColsA;j++){
                cout << A[i][j] << " " ;
            }
            cout << endl;
        }
        for(int i = 0; i < RowsB; i++){
            for(int j = 0; j < ColsB;j++){
                cout << B[i][j] << " " ;
            }
            cout << endl;
        }

        for(int i = 0; i < ColsPi; i++){
            cout << Pi[i] << " " ;
        }
        cout << endl;

        for(int i = 0; i < Observations; i++){
            cout << obs[i] << " " ;
        }
        cout << endl;

    return;
}

void Lambda::EmissionProbability(){

    float AB = 0;
    float PiA = 0;
    float PiAB = 0;

    for(int i=0; i<RowsA; i++){
        for(int j=0; j<ColsB; j++){
            for(int k=0; k < ColsA && k < RowsB; k++){
                AB += A[i][k]*B[k][j];
            }
            AxB[i][j] = (double)AB;
            AB = 0;
        }
    }
    //Pi*A
    for(int j=0; j<ColsA; j++){
            for(int k=0; k< ColsA&& k < RowsA; k++){
                PiA += Pi[k]*A[k][j];
            }
            PixA[j] = PiA;
            PiA = 0;
    }

    //Pi*AB
    for(int j=0; j<ColsA; j++){
            for(int k=0; k< ColsA&& k < RowsB; k++){
                PiAB +=Pi[k]*AxB[k][j];
            }
            ProbabilityVector[j] = PiAB;
            PiAB = 0;
    }
}

void Lambda::ForwardAlg(){      //forward algorithm
 c[0] = 0;
    for( int i = 0; i < ColsA ; i++){       //Compute alpha 0
        Alpha[i][0] = Pi[i]*B[i][obs[0]];
        c[0] += Alpha[i][0];      //Scaling parameters
    }
    c[0] = 1/c[0];
    for( int i = 0; i < ColsA ; i++){       //Scaling
        Alpha[i][0] *= c[0];
    }
    for(int j = 0; j < Observations - 1 ; j++){
        c[j+1] = 0;
        for( int k= 0; k < ColsA ; k++){
            Alpha[k][j+1] = 0;
            for(int m = 0; m < RowsA; m++ ){
                Alpha[k][j+1] += Alpha[m][j]*A[m][k];       //Compute alpha t
            }
            Alpha[k][j+1] *= B[k][obs[j+1]];
            c[j+1] += Alpha[k][j+1];
        }
        c[j+1]= 1/c[j+1];
        for(int m = 0; m < ColsA; m++ ){
               Alpha[m][j+1] *= c[j+1];     //Scaling
        }
    }
    for( int i = 0; i < RowsB; i++){
            SecuenceProbability += Alpha[i][Observations - 1];      //Compute probability
    }
    //cout << SecuenceProbability;
}

void Lambda::ViterbiAlg(){
    //Pi*B init
    double * AuxMax;
    double Max = 0;
    int AuxSeq = NO_RUTE;
    AuxMax =(double *) malloc(RowsA*sizeof(double));

    for( int i = 0; i < RowsB ; i++){
        Delta[i][0] = Pi[i]*B[i][obs[0]];       //Compute gamma 0
        statesSeq[i][0] = NO_RUTE;
    }

    for(int j = 0; j < Observations - 1 ; j++){
        for( int k= 0; k < ColsA ; k++){
            for(int m = 0; m < RowsA; m++ ){
               AuxMax[m] = Delta[m][j]*A[m][k]*B[k][obs[j+1]];      //Compute the different sequences
            }
            for( int n = 0; n < RowsA ; n++){       //Take the most probable jump
                if(AuxMax[n] > Max){
                    Max = AuxMax[n];
                    AuxSeq = n;
                }
            }
            Delta[k][j+1] = Max;        //Compute gamma t
            statesSeq[k][j+1] = AuxSeq;     //Store the sequence
            Max = 0;
            AuxSeq = NO_RUTE;
        }
    }
    Max = 0;

    for( int i = 0; i < RowsB; i++){
        if(Delta[i][Observations-1] >= Max){        //Compute the most probable jump
            Max = Delta[i][Observations-1];
            AuxSeq = i;
        }
    }
    ProbableSeq[Observations - 1] = AuxSeq;     //Compute most probable sequence
    for( int i = Observations - 2; i >= 0; i--){
       ProbableSeq[i] = statesSeq[AuxSeq][i + 1];
       AuxSeq = statesSeq[AuxSeq][i + 1];
    }
}

void Lambda::Output(){
    for(int i = 0; i < Observations ; i++){
        cout << ProbableSeq[i] << " ";
    }
}

int main()
{
    Lambda Test;
    Test.ForwardAlg();
    Test.ViterbiAlg();
    Test.Output();
    return 0;
}
