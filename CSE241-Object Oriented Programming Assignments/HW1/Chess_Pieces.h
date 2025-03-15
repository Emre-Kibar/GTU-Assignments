#ifndef _CHESS_PIECE_H
#define _CHESS_PIECE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Piece{
	public:
		Piece(char _name = '.', double _value = 0.0, bool _underThreatWhite = false, bool _underThreatBlack = false) 
                    : name(_name), value(_value), underThreatWhite(_underThreatWhite), underThreatBlack(_underThreatBlack){}

        friend ostream& operator <<(ostream& outStream, const Piece& obj);
        friend class ChessBoard;
        
	private:
        char name;
        double value;
        bool underThreatWhite;
        bool underThreatBlack;

        void setName(const char _name){ name = _name; };
        void setValue(const double _value){ value = _value; };
        char getName(){ return name; }
        double getValue(){ return value; }
        void setunderThreatWhite(bool _underThreat){ underThreatWhite = _underThreat; };
        bool getunderThreatWhite(){ return underThreatWhite; }
        void setunderThreatBlack(bool _underThreat){ underThreatBlack = _underThreat; };
        bool getunderThreatBlack(){ return underThreatBlack; }
};

#endif // _CHESS_PIECE_H