#ifndef _CHESS_BOARD_H
#define _CHESS_BOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Chess_Pieces.h"
using namespace std;

class ChessBoard{
	public:
		ChessBoard() : board(8, vector<Piece>(8)), moveCounter(0), firstMove(0){}
		
        void playGame();
    
    private:
    	vector< vector<Piece> > board;
        int moveCounter;
        bool firstMove;

        void initializeBoard();
		void printBoard() const;
        void saveMovesFile(ofstream& fout) const;
        void updateBoard(string& input);
        bool checkMoveValidatiy(int beginRow, int beginCol, int finalRow, int finalCol);
        void setFirstMove(bool value){ firstMove = value; }
        bool getunderThreat(const int& beginRow,const int& beginCol,const int& nextRow,const int& nextCol);
        bool isKingMoveable(int row, int col);
        bool isGameFinished();
        bool isCheck(int beginRow, int beginCol, int finalRow, int finalCol);
        void takeInput();

        void checkUnderThreatWhite(bool status);
        void checkUnderThreatBlack(bool status);
        void checkUnderThreat(bool status);
        void setThreatHorizontal(int row, int col, bool status);
        void setThreatVertical(int row, int col, bool status);
        void setThreatDiagonal(int row, int col, bool status);
        void setThreatPawn(int row,int col, bool status);
        void setThreatRook(int row,int col, bool status);
        void setThreatKnight(int row,int col, bool status);
        void setThreatBishop(int row,int col, bool status);
        void setThreatQueen(int row,int col, bool status);
        void setThreatKing(int row,int col, bool status);
        const double calculateScoreWhite();
        const double calculateScoreBlack();
        void printScore();

        bool isOverride(const char pieceName);
        bool controlMoveHorizontal(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool controlMoveVertical(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool controlMoveDiagonal(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool movePawn(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool moveRook(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool moveKnight(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool moveBishop(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool moveQueen(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
        bool moveKing(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol);
};
#endif // _CHESS_BOARD_H