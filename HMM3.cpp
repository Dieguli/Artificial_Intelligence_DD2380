#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#define space " "
#define NO_RUTE -1
#define ORIGINAL 1
#define AUX 0

#define MAX_ITERS 1000
//HMM4
using namespace std;

class Lambda{
    private:
        double **A;
        double **B;
        double *Pi;
        double **Alpha;
        double **Beta;
        double ***DiGamma;
        double ** Gamma;
        int * obs;
        double *c;
        int Observations;
        int ColsA;
        int RowsA;
        int ColsB;
        int RowsB;
        int ColsPi;
        int RowsPi;
        int Iterations = 0;
        double logProb;
        double oldLogProb = -100000;

    public:
        Lambda();
        ~Lambda();
        void MatrixSize();
        void ReadData();
        void ShowMatrix();
        void ForwardAlg();
        void BetaAlg();
        void GetGamma();
        void BWAlg();
        void NewValues();
        void Output();

};

Lambda::Lambda(){       //Matrices allocation

    ReadData();

    Alpha =(double **) malloc(ColsA*sizeof(double *));

    for(int i = 0;i < ColsA;i++)
        Alpha[i] = (double *) malloc(Observations*sizeof(double));

    Beta =(double **) malloc(ColsA*sizeof(double *));

    for(int i = 0;i < ColsA;i++)
        Beta[i] = (double *) malloc(Observations*sizeof(double));


    DiGamma =(double ***) malloc(Observations*sizeof(double **));

    for(int i = 0;i < Observations;i++){
        DiGamma[i] = (double **) malloc(RowsA*sizeof(double*));
        for(int j = 0; j < RowsA; j++){
            DiGamma[i][j] = (double *) malloc(RowsA*sizeof(double));
        }
    }

    Gamma =(double **) malloc(ColsA*sizeof(double *));
    for(int i = 0;i < ColsA;i++)
        Gamma[i] = (double *) malloc(Observations*sizeof(double));

    c = (double *) malloc(Observations*sizeof(double));
}

Lambda::~Lambda(){
    for (int i=0; i<RowsA;i++)
        free(A[i]);
    free (A);
    for (int i=0; i<RowsA;i++)
        free(B[i]);
    free(B);
    free(Pi);
    for (int i=0; i<ColsA;i++)
        free(Alpha[i]);
    free(Alpha);
    free(obs);
    free(c);
    for (int i=0; i<ColsA;i++)
        free(Beta[i]);
    free(Beta);
    for (int i=0; i<ColsA;i++)
        free(Gamma[i]);
    free(Gamma);
    for(int i = 0;i < Observations;i++){
        for(int j = 0; j < RowsA; j++){
           free( DiGamma[i][j] );
        }
         free(DiGamma[i]);
    }
    free(DiGamma);
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
        cout << endl;
        for(int i = 0; i < RowsB; i++){
            for(int j = 0; j < ColsB;j++){
                cout << B[i][j] << " " ;
            }
            cout << endl;
        }
        cout << endl;
        for(int i = 0; i < ColsPi; i++){
            cout << Pi[i] << " " ;
        }
    return;
}

void Lambda::Output(){      //Gives rows, columns and values of the matrices
    cout << RowsA << " " << ColsA << " ";
        for(int i = 0; i < RowsA; i++){
            for(int j = 0; j < ColsA;j++){
                cout << (float)A[i][j] << " " ;
            }
        }
        cout << endl;
        cout << RowsB << " " << ColsB << " ";
        for(int i = 0; i < RowsB; i++){
            for(int j = 0; j < ColsB; j++){
                cout << (float)B[i][j] << " ";
            }
        }
    return;
}

void Lambda::ForwardAlg( ){     //Forward algorithm
    c[0] = 0;
    for( int i = 0; i < ColsA ; i++){   //Compute alpha 0
        Alpha[i][0] = Pi[i]*B[i][obs[0]];
        c[0] += Alpha[i][0];        //Scaling parameters
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
    double Prob = 0;
}


void Lambda::BetaAlg(){
    //Init B(t=T) = 1
    for( int i = 0; i < ColsA ; i++ ){
       Beta[i][Observations - 1] = c[Observations - 1];
    }
    for(int j = Observations - 2; j >=0 ; j--){
        for( int k = 0; k < ColsA ; k++){
        Beta[k][j] = 0;
            for(int m = 0; m < ColsA; m++ ){
                Beta[k][j] += Beta[m][j + 1]*A[k][m]*B[m][obs[j+1]];        //Compute Beta t from t+1
            }
        Beta[k][j] *= c[j];
        }
    }
}

void Lambda::GetGamma(){
    double Den;
    for(int t = 0; t < Observations - 1; t++){
        Den = 0;
        for(int i = 0; i < ColsA; i++){
            for(int j = 0; j < ColsA; j++){
                Den += Alpha[i][t]*A[i][j]*B[j][obs[t+1]]*Beta[j][t+1];     //Compute denominator
            }
        }
        for( int i = 0; i < ColsA; i++){
            Gamma[i][t] = 0;
            for(int j = 0; j < ColsA; j++){
                DiGamma[t][i][j] = Alpha[i][t]*A[i][j]*B[j][obs[t+1]]*Beta[j][t+1]/Den;     //Compute digamma
                Gamma[i][t] += DiGamma[t][i][j];
            }
        }
    }
    Den = 0;
    for( int i = 0; i < ColsA; i++){
        Den += Alpha[i][Observations-1];
    }
    for( int i = 0; i < ColsA; i++){
        Gamma[i][Observations - 1] = Alpha[i][Observations - 1]/Den;      //Compute gamma
    }
}

void Lambda::NewValues(){       //Re-estimations
    double Num = 0;
    double Den = 0;
    for(int i = 0; i < ColsA ; i++){        //Re-estimate Pi
        Pi[i] = Gamma[i][0];
    }
    for(int i = 0; i < ColsA; i++){
        for(int j = 0; j < ColsA; j ++){
            Num = 0;
            Den = 0;
            for( int t = 0; t < Observations - 1; t++){
                Num += DiGamma[t][i][j];
                Den += Gamma[i][t];
            }
            A[i][j] = Num/Den;          //Re-estimate A
        }
    }
    for(int i = 0; i < ColsA; i++){
        for(int j = 0; j < ColsB; j++){
            Num = 0;
            Den = 0;
            for( int t = 0; t < Observations; t++){
                if( obs[t] == j) {   Num += Gamma[i][t];}
                Den += Gamma[i][t];
            }
            B[i][j] = Num/Den;          //Re-estimate B
        }
    }
}

void Lambda::BWAlg(){

    while( Iterations < MAX_ITERS){      //Decide if do next iteration
        ForwardAlg();
        BetaAlg();
        logProb = 0;
        for(int i = 0; i < Observations; i++){      //Compute log of probability
            logProb += log10(c[i]);
        }
        logProb = -logProb;
        Iterations++;
        oldLogProb = logProb;
        GetGamma();
        NewValues();
    }
    return;
}

int main()
{
    Lambda Test;
    Test.BWAlg();
    Test.Output();
    return 0;
}


