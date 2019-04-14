//3D def
#include "player.hpp"
#include <cstdlib>

namespace TICTACTOE3D
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

      std::vector<GameState> lNextStates; 

    int v = -100000000; 
    int index = 0;
    pState.findPossibleMoves(lNextStates);

    uint8_t nextPlayer = pState.getNextPlayer();

    int alpha = -initialgain;
    int beta = initialgain;
    int stateAux, indexAux;
    int * childState = (int *) malloc( lNextStates.size()*sizeof(int));
    int * childsIndex = (int *) malloc( lNextStates.size()*sizeof(int));
    int minmaxout;



    for(int i = 0; i < lNextStates.size(); i++){
            childState[i] = evaluationFunction(lNextStates[i]);
            childsIndex[i] = i;

    }
   
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
    if (lNextStates.size() == 0) return GameState(pState, Move());

    else{
        for( int i = 0; i < lNextStates.size(); i++){
            minmaxout = minimax(lNextStates[childsIndex[i]], nextPlayer,alpha, beta, maximunDepth - 1); 
            if( minmaxout >= v){
                v = minmaxout;
                index = childsIndex[i];
            }
            /*if( minmaxout >= (points/10)){
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

    //----------------------Possible movements--------------------
    std::vector<GameState> NextStates;
    pState.findPossibleMoves(NextStates);
    //----------------------------------------------------------------------------------------------------

    int orden, indice;
    int * States = (int *) malloc( NextStates.size()*sizeof(int));
    int * Indices = (int *) malloc( NextStates.size()*sizeof(int));

    if( NextStates.size() == 0){
        return GameOver( previousMove, currentPlayer, depth);
    }
    if(depth == 0){return evaluationFunction(pState); } 
   
    else{
     if(depth == 1){ 
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
       return  (points - depth);
                //return (points + depth);

    }
    else if(lastMove.isOWin()){
        return (points + depth);
               // return (-points );

        
    }
    else if(lastMove.isDraw()) return 0;
}
int Player::evaluationFunction(const GameState &pState){

int values[5] = {1,10,100,1000,points};//{0,1,30,5000,points}
    int sumX = 0;
    int sumO = 0;
    int sumRowsX = 0;
    int sumRowsO = 0;
    int sumDepthO = 0;
    int sumDepthX = 0;
    int sumColsO = 0;
    int sumColsX = 0;
    int sumDiag1X = 0;
    int sumDiag1O = 0;
    int sumDiag2X = 0;
    int sumDiag2O = 0;
    int sumDiag3X = 0;
    int sumDiag3O = 0;
    int sumDiag4X = 0;
    int sumDiag4O = 0;
    int sumDiag5X = 0;
    int sumDiag5O = 0;
    int sumDiag6X = 0;
    int sumDiag6O = 0;
    int sumGen1X = 0;
    int sumGen1O = 0;
    int sumGen2X = 0;
    int sumGen2O = 0;
    int sumGen3X = 0;
    int sumGen3O = 0;
    int sumGen4X = 0;
    int sumGen4O = 0;
    int puntuacion = 0;

  
    for( int k = 0; k < 4; k++){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(pState.at(i,j,k) == CELL_X){
                    sumColsX++;
                }
                else if(pState.at(i,j,k) == CELL_O){
                    sumColsO++;
                }
                /*if(pState.at(k,i,j) == CELL_X){
                    sumDepthX++;
                }
                else if(pState.at(k,i,j) == CELL_O){
                    sumDepthO++;
                }*/
                if(pState.at(j,i,k) == CELL_X){
                    sumRowsX++;
                }
                else if(pState.at(j,i,k) == CELL_O){
                    sumRowsO++;
                }

            }
          /* if (sumDepthO == 0){
                puntuacion += values[sumDepthX];
            }
            else if (sumDepthX == 0){
                puntuacion -= 2*values[sumDepthO];
            }*/
            if (sumColsO == 0){
                puntuacion += values[sumColsX];
            }
            else if (sumColsX == 0){
                puntuacion -= values[sumColsO];
            }
            if (sumRowsO == 0){
                puntuacion += values[sumRowsX];
            }
            else if (sumRowsX == 0){
                puntuacion -= values[sumRowsO];
            }
            sumRowsX = 0;
            sumRowsO = 0;
            sumDepthO = 0;
            sumDepthX = 0;
            sumColsO = 0;
            sumColsX = 0;

            if(pState.at(i,i,k) == CELL_X){
                sumDiag1X++;
            }
            else if(pState.at(i,i,k) == CELL_O){
                sumDiag1O++;
            }
            if(pState.at(i,3-i,k) == CELL_X){
                sumDiag2X++;
            }
            else if(pState.at(i,3-i,k) == CELL_O){
                sumDiag2O++;
            }
            if(pState.at(i,k,i) == CELL_X){
                sumDiag3X++;
            }
            else if(pState.at(i,k,i) == CELL_O){
                sumDiag3O++;
            }
            if(pState.at(3-i,k,i) == CELL_X){
                sumDiag4X++;
            }
            else if(pState.at(3-i,k,i) == CELL_O){
                sumDiag4O++;
            }
             if(pState.at(k,i,i) == CELL_X){
                sumDiag5X++;
            }
            else if(pState.at(k,i,i) == CELL_O){
                sumDiag5O++;
            }
            if(pState.at(k,i,3-i) == CELL_X){
                sumDiag6X++;
            }
            else if(pState.at(k,i,3-i) == CELL_O){
                sumDiag6O++;
            }
        }
        if (sumDiag1O == 0){
            puntuacion += values[sumDiag1X];
        }
        else if (sumDiag1X == 0){
            puntuacion -= values[sumDiag1O];
        }
        if (sumDiag2O == 0){
            puntuacion += values[sumDiag2X];
        }
        else if (sumDiag2X == 0){
            puntuacion -= values[sumDiag2O];
        }
        if (sumDiag3O == 0){
            puntuacion += values[sumDiag3X];
        }
        else if (sumDiag3X == 0){
            puntuacion -= values[sumDiag3O];
        }
        if (sumDiag4O == 0){
            puntuacion += values[sumDiag4X];
        }
        else if (sumDiag4X == 0){
            puntuacion -= values[sumDiag4O];
        }
        if (sumDiag5O == 0){
            puntuacion += values[sumDiag5X];
        }
        else if (sumDiag5X == 0){
            puntuacion -= values[sumDiag5O];
        }
        if (sumDiag6O == 0){
            puntuacion += values[sumDiag6X];
        }
        else if (sumDiag6X == 0){
            puntuacion -= values[sumDiag6O];
        }
        sumDiag1X = 0;
        sumDiag1O = 0;
        sumDiag2X = 0;
        sumDiag2O = 0;
        sumDiag3X = 0;
        sumDiag3O = 0;
        sumDiag4X = 0;
        sumDiag4O = 0;
        sumDiag5X = 0;
        sumDiag5O = 0;
        sumDiag6X = 0;
        sumDiag6O = 0;

        if(pState.at(k,k,k) == CELL_X){
            sumGen1X++;
        }
        else if(pState.at(k,k,k) == CELL_O){
            sumGen1O++;
        }
        if(pState.at(k,3-k,k) == CELL_X){
            sumGen2X++;
        }
        else if(pState.at(k,3-k,k) == CELL_O){
            sumGen2O++;
        }
        if(pState.at(3-k,k,k) == CELL_X){
            sumGen3X++;
        }
        else if(pState.at(3-k,k,k) == CELL_O){
            sumGen3O++;
        }
         if(pState.at(k,k,3-k) == CELL_X){
            sumGen4X++;
        }
        else if(pState.at(k,k,3-k) == CELL_O){
            sumGen4O++;
        }
    }
    if (sumGen1O == 0){
        puntuacion += values[sumGen1X];
    }
    else if (sumGen1X == 0){
        puntuacion -= values[sumGen1O];
    }
    if (sumGen2O == 0){
        puntuacion += values[sumGen2X];
    }
    else if (sumGen2X == 0){
        puntuacion -= values[sumGen2O];
    }
     if (sumGen3O == 0){
        puntuacion += values[sumGen3X];
    }
    else if (sumGen3X == 0){
        puntuacion -= values[sumGen3O];
    }
     if (sumGen4O == 0){
        puntuacion += values[sumGen4X];
    }
    else if (sumGen4X == 0){
        puntuacion -= values[sumGen4O];
    }
    
    
    sumGen1X = 0;
    sumGen1O = 0;
    sumGen2X = 0;
    sumGen2O = 0;
    sumGen3X = 0;
    sumGen3O = 0;
    sumGen4X = 0;
    sumGen4O = 0;


     return (puntuacion);
}

/*namespace TICTACTOE*/ }



