//2D def
#include "player.hpp"
#include <cstdlib>

//Result: 23 points in Kattis
namespace TICTACTOE
{

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    /*std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);


    if (lNextStates.size() == 0) return GameState(pState, Move());*/

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */

      std::vector<GameState> lNextStates; // array for storing possible movements

    int v = -100000000; // variable equal to points
    int index = 0;
    pState.findPossibleMoves(lNextStates);

    uint8_t nextPlayer = pState.getNextPlayer();

    int alpha = -initialgain;
    int beta = initialgain;
    int stateAux, indexAux;
    int * childState = (int *) malloc( lNextStates.size()*sizeof(int));
    int * childsIndex = (int *) malloc( lNextStates.size()*sizeof(int));
    int minmaxout;

// First, an evaluation about the possible movements is carried out.

    for(int i = 0; i < lNextStates.size(); i++){
            childState[i] = evaluationFunction(lNextStates[i]);
            childsIndex[i] = i;

    }
    // Comparing the values of the different sates so that the most interesting order is found.
    for(int i = 0; i < lNextStates.size()-1; i++){
        for(int j = 1;j < lNextStates.size(); j++){
                if(childState[i] >= childState[j]){
                    stateAux = childState[j];
                    indexAux = childsIndex[j];
                    childsIndex[j] = childsIndex[i];
                    childState[j] = childState[i];
                    childsIndex[i] = indexAux;
                    childState[i] = stateAux;
                }

        }
    }
    if (lNextStates.size() == 0) return GameState(pState, Move());// End of the game

    else{
        for( int i = 0;i < lNextStates.size(); i++){
            minmaxout = minimax(lNextStates[childsIndex[i]], nextPlayer,alpha, beta, maximunDepth - 1); // minmax is applied in the most interesting order
            if( minmaxout >= v){
                v = minmaxout;
                index = childsIndex[i];
            }/*
            if( minmaxout >= (points/10)){
                return lNextStates[childsIndex[i]];
            }*/
        }
        return lNextStates[index];
    }
}

//minimax (current state we are analizying, the current player, the current best value available by A, the current best sate avilale by B)
int Player::minimax(const GameState &pState, uint8_t &child,int alpha, int beta,int depth){
    int bestChoice;
    //Get the last move made (the move that lead to this state)
    Move previousMove = pState.getMove();

    uint8_t currentPlayer = child;
    uint8_t nextPlayer = pState.getNextPlayer(); 

    //----------------------Get the possible movements of the current state--------------------
    std::vector<GameState> NextStates;
    pState.findPossibleMoves(NextStates);
    //----------------------------------------------------------------------------------------------------

    int orden, indice;
    int * States = (int *) malloc( NextStates.size()*sizeof(int));
    int * Indices = (int *) malloc( NextStates.size()*sizeof(int));

    if( NextStates.size() == 0){
        return GameOver( previousMove, currentPlayer, depth);
    }//terminal state
    if(depth == 0){return evaluationFunction(pState); } 
   
    else{ //depth == 1
     if(depth >= 1){ 
    for(int i = 0; i < NextStates.size(); i++){
            States[i] = evaluationFunction(NextStates[i]);
            Indices[i] = i;

    }
    for(int i = 0; i < NextStates.size()-1; i++){
        for(int j = 1;j < NextStates.size(); j++){
                if(States[i] >= States[j]){
                    orden = States[j];
                    indice = Indices[j];
                    Indices[j] = Indices[i];
                    States[j] = States[i];
                    Indices[i] = indice;
                    States[i] = orden;
                }

        }
    }

        if( currentPlayer == CELL_X){
                for(int i = 0; i < NextStates.size(); i++){
                    alpha = std::max(alpha,minimax(NextStates[Indices[i]], nextPlayer,alpha, beta, depth - 1));
                    if(beta <= alpha) break;
                }
                return alpha;
        }
        else{
                for(int i = NextStates.size() - 1; i >= 0; i--){
                   beta = std::min(beta,minimax(NextStates[Indices[i]], nextPlayer, alpha, beta, depth - 1));
                   if(beta <= alpha) break;
                }
                return beta;
        }
    }
    else{ if( currentPlayer == CELL_X){
                for(int i = 0; i < NextStates.size(); i++){
                    alpha = std::max(alpha,minimax(NextStates[i], nextPlayer,alpha, beta, depth - 1));
                    if(beta <= alpha) break;
                }
                return alpha;
        }
        else{
                for(int i = NextStates.size() - 1; i >= 0; i--){
                   beta = std::min(beta,minimax(NextStates[i], nextPlayer, alpha, beta, depth - 1));
                   if(beta <= alpha) break;
                }
                return beta;
        }}
    }
}
int Player::GameOver ( const Move &lastMove, uint8_t &currPlayer, int depth){

    if( lastMove.isXWin()){
      // return  (points - depth);
      return  (points);
    }
    else if(lastMove.isOWin()){
        //return (points + depth);
        return (-points);
    }
    else if(lastMove.isDraw()) return 0;
}

int Player::evaluationFunction(const GameState &pState){

int values[5] = {1,10,100,1000,points};
   //----------------boxes-----------------
    int sumX = 0;
    int sumO = 0;
//----------------rows-----------------
    int sumRowsO = 0;
    int sumRowsX = 0;
    //----------------colums-----------------
    int sumColsO = 0;
    int sumColsX = 0;
    //----------------diagonals-----------------
    int sumDiagX = 0;
    int sumDiagO = 0;

    int puntuacion = 0;

   

    for( int k = 0; k < 4; k++){
        for(int i = 0; i < 4; i++){

            if(pState.at(i,k) == CELL_X){
                    sumColsX++;
                }
                else if(pState.at(i,k) == CELL_O){
                    sumColsO++;
                }
                 if(pState.at(k,i) == CELL_X){
                    sumRowsX++;
                }
                else if(pState.at(k,i) == CELL_O){
                    sumRowsO++;
                }
        }
        if (sumRowsO == 0){
                puntuacion += values[sumRowsX];
            }
            else if (sumRowsX == 0){
                puntuacion -= values[sumRowsO];
            }
            if (sumColsO == 0){
                puntuacion += values[sumColsX];
            }
            else if (sumColsX == 0){
                puntuacion -= values[sumColsO];
            }
          sumRowsX = 0;
            sumRowsO = 0;
            sumColsO = 0;
            sumColsX = 0; 
}
        
   
        for(int i = 0; i < 4; i++){
        if(pState.at(i,i) == CELL_X){
                    sumDiagX++;
                }
                else if(pState.at(i,i) == CELL_O){
                    sumDiagO++;
                }
        
        }
     if (sumDiagO== 0){
                puntuacion += values[sumDiagX];
            }
            else if (sumDiagX == 0){
                puntuacion -= values[sumDiagO];}
    
            sumDiagX =0;
            sumDiagO = 0;
            
         /*for(int i = 3; i>=0; --i){
        if(pState.at(i,i) == CELL_X){
                    sumDiagX++;
                }
                else if(pState.at(i,i) == CELL_O){
                    sumDiagO++;
                }
           if (sumDiagO== 0){
                puntuacion += values[sumDiagX];
            }
            else if (sumDiagX == 0){
                puntuacion -= values[sumDiagO];}}      
        
       
            
    if (sumDiagO== 0){
                puntuacion += values[sumDiagX];
            }
            else if (sumDiagX == 0){
                puntuacion -= values[sumDiagO];} */
        
            sumRowsX = 0;
            sumRowsO = 0;
            sumColsO = 0;
            sumColsX = 0;
            sumDiagX = 0;
            sumDiagO= 0;

return (puntuacion);
}
    
}




    //return lNextStates[rand() % lNextStates.size()];


/*namespace TICTACTOE*/ 
