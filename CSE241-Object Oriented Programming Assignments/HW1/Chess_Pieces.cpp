#include "Chess_Pieces.h"
#include "Chess_Board.h"

ostream& operator <<(ostream& outStream, const Piece& obj){
    outStream << obj.name;
    return outStream;
}