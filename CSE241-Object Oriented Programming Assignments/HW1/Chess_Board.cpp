#include "Chess_Board.h"
#include "Chess_Pieces.h"

void ChessBoard :: initializeBoard(){
    //Set white and black piece on the board.
    board[0][0] = Piece{'R', 5.0};
    board[0][1] = Piece{'N', 3.0};
    board[0][2] = Piece{'B', 3.0};
    board[0][3] = Piece{'Q', 9.0};
    board[0][4] = Piece{'K', 100.0};
    board[0][5] = Piece{'B', 3.0};
    board[0][6] = Piece{'N', 3.0};
    board[0][7] = Piece{'R', 5.0};
    for (int i = 0; i < 8; ++i) {
        board[1][i] = Piece{'P', 1.0};
    }

    board[7][0] = Piece{'r', 5.0};
    board[7][1] = Piece{'n', 3.0};
    board[7][2] = Piece{'b', 3.0};
    board[7][3] = Piece{'q', 9.0};
    board[7][4] = Piece{'k', 100.0};
    board[7][5] = Piece{'b', 3.0};
    board[7][6] = Piece{'n', 3.0};
    board[7][7] = Piece{'r', 5.0};
    for (int i = 0; i < 8; ++i) {
        board[6][i] = Piece{'p', 1.0};
    }

    checkUnderThreat(true); //Determine which pieces is threated by white and black pieces
}

void ChessBoard :: printBoard() const{
    //print the chess board and pieces.
    for(int i=7; i >= 0; --i){
    	cout << i+1 << "  |  ";  
		for(int j=0; j <= 7; ++j){
            cout<<board[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "    -------------------------" << endl;
    cout << "    " << "  a  " << "b  " << "c  " << "d  "<< "e  "<< "f  "<< "g  "<< "h  " << endl;
}

void ChessBoard::setThreatHorizontal(int row, int col, bool status){
    char name = board[row][col].getName();
    
    for(int i = col + 1; i < 8; ++i){  //set threat values of the locations on the righthend side of the selected piece.
        if(board[row][i].getName() == '.'){ //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[row][i].setunderThreatWhite(status);
            }else if (name >= 'a' && name <= 'z'){
                board[row][i].setunderThreatBlack(status);
            }
        }else{
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if(name >= 'A' && name <= 'Z'){
                board[row][i].setunderThreatWhite(status);
            }else if (name >= 'a' && name <= 'z'){
                board[row][i].setunderThreatBlack(status);
            }
            break;
        }
    }

    for(int i = col - 1; i >= 0; --i){  //set threat values of the locations on the leftend side of the selected piece.
        if(board[row][i].getName() == '.'){   //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[row][i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[row][i].setunderThreatBlack(status);
            }
        }else{
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if(name >= 'A' && name <= 'Z'){
                board[row][i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[row][i].setunderThreatBlack(status);
            }
            break;
        }
    }
}

void ChessBoard::setThreatVertical(int row, int col, bool status) {
    char name = board[row][col].getName();

    for(int i = row + 1; i < 8; ++i){ //set threat values of the locations on the upward side of the selected piece.
        if(board[i][col].getName() == '.'){  //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[i][col].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[i][col].setunderThreatBlack(status);
            }
        } else {
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if(name >= 'A' && name <= 'Z'){
                board[i][col].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[i][col].setunderThreatBlack(status);
            }
            break;
        }
    }

    for(int i = row - 1; i >= 0; --i){    //set threat values of the locations on the downward side of the selected piece.
        if(board[i][col].getName() == '.'){  //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' and name <= 'Z'){
                board[i][col].setunderThreatWhite(status);
            }else if(name >= 'a' and name <= 'z'){
                board[i][col].setunderThreatBlack(status);
            }
        }else{
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if(name >= 'A' && name <= 'Z'){
                board[i][col].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[i][col].setunderThreatBlack(status);
            }
            break;
        }
    }
}

void ChessBoard::setThreatDiagonal(int row, int col, bool status){
    char name = board[row][col].getName();

    // Threaten squares along the top-left to bottom-right diagonal
    for(int i = 1; row + i < 8 && col + i < 8; ++i){  
        if(board[row + i][col + i].getName() == '.'){    //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[row + i][col + i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[row + i][col + i].setunderThreatBlack(status);
            }
        }else{
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if(name >= 'A' && name <= 'Z'){
                board[row + i][col + i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[row + i][col + i].setunderThreatBlack(status);
            }
            break;
        }
    }

    for(int i = 1; row - i >= 0 && col - i >= 0; ++i){
        if(board[row - i][col - i].getName() == '.'){  //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[row - i][col - i].setunderThreatWhite(status);
            }else if(name >= 'a' and name <= 'z'){
                board[row - i][col - i].setunderThreatBlack(status);
            }
        } else {
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if (name >= 'A' && name <= 'Z') {
                board[row - i][col - i].setunderThreatWhite(status);
            } else if (name >= 'a' && name <= 'z') {
                board[row - i][col - i].setunderThreatBlack(status);
            }
            break;
        }
    }

    // Threaten squares along the top-right to bottom-left diagonal
    for(int i = 1; row - i >= 0 && col + i < 8; ++i){
        if(board[row - i][col + i].getName() == '.'){   //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[row - i][col + i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[row - i][col + i].setunderThreatBlack(status);
            }
        }else{
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if(name >= 'A' && name <= 'Z'){
                board[row - i][col + i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z'){
                board[row - i][col + i].setunderThreatBlack(status);
            }
            break;
        }
    }

    for(int i = 1; row + i < 8 && col - i >= 0; ++i){
        if(board[row + i][col - i].getName() == '.'){   //if location is empty,then keeping set underThreat values according to piece type of selected location.
            if(name >= 'A' && name <= 'Z'){
                board[row + i][col - i].setunderThreatWhite(status);
            }else if(name >= 'a' && name <= 'z') {
                board[row + i][col - i].setunderThreatBlack(status);
            }
        } else {
            // Threaten the piece and stop when reaching a piece whether it's an enemy or own piece
            if (name >= 'A' && name <= 'Z') {
                board[row + i][col - i].setunderThreatWhite(status);
            } else if (name >= 'a' && name <= 'z') {
                board[row + i][col - i].setunderThreatBlack(status);
            }
            break;
        }
    }
}

void ChessBoard::setThreatPawn(int row, int col, bool status){
    // set threat values to diagonal capture locations according to piece type
    if(board[row][col].getName() >= 'A' && board[row][col].getName() <= 'Z'){
        if(row + 1 <= 7 && col - 1 >= 0)
            board[row + 1][col - 1].setunderThreatWhite(status);
        if(row + 1 <= 7 && col + 1 <= 7)
            board[row + 1][col + 1].setunderThreatWhite(status);
    }else if(board[row][col].getName() >= 'a' && board[row][col].getName() <= 'z'){
        if (row - 1 >= 0 && col - 1 >= 0)
            board[row - 1][col - 1].setunderThreatBlack(status);
        if (row - 1 >= 0 && col + 1 <= 7)
            board[row - 1][col + 1].setunderThreatBlack(status);
    }
}

void ChessBoard::setThreatRook(int row, int col, bool status){
    //set threat values for possible horizontal and vertical locations for rook
    setThreatHorizontal(row, col, status);
    setThreatVertical(row, col, status);
}

void ChessBoard::setThreatKnight(int row, int col, bool status){
    //knightMoves vector holds possible knight moves
    vector< vector<int> > knightMoves = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1},
                                       {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    //If knightMoves is holds for board boundraies,then set underThreat values according to the piece type
    for(const auto &move : knightMoves){
        int newRow = row + move[0];
        int newCol = col + move[1];

        if(newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8){
            if(board[row][col].getName() >= 'A' && board[row][col].getName() <= 'Z'){
                board[newRow][newCol].setunderThreatWhite(status);
            }else if(board[row][col].getName() >= 'a' && board[row][col].getName() <= 'z'){
                board[newRow][newCol].setunderThreatBlack(status);
            }
        }
    }
}

void ChessBoard::setThreatBishop(int row, int col, bool status){
    //set threat values for possible diagonal locations for bishop
    setThreatDiagonal(row, col, status);
}

void ChessBoard::setThreatQueen(int row, int col, bool status){
    //set threat values for possible horizontal,vertical and diagonal locations for queen
    setThreatHorizontal(row, col, status);
    setThreatVertical(row, col, status);
    setThreatDiagonal(row, col, status);
}

void ChessBoard::setThreatKing(int row, int col, bool status){
    //kingMoves vector holds possible king moves
    vector<vector<int>> kingMoves = {{-1, -1}, {-1, 0}, {-1, 1},
                                     {0, -1},           {0, 1},
                                     {1, -1}, {1, 0}, {1, 1}};

    //If kingMoves is holds for board boundraies,then set underThreat values according to the piece type
    for(const auto &move : kingMoves){
        int newRow = row + move[0];
        int newCol = col + move[1];

        if(newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if(board[row][col].getName() >= 'A' && board[row][col].getName() <= 'Z'){
                board[newRow][newCol].setunderThreatWhite(status);
            }else if(board[row][col].getName() >= 'a' && board[row][col].getName() <= 'z'){
                board[newRow][newCol].setunderThreatBlack(status);
            }
        }
    }
}

void ChessBoard:: checkUnderThreatWhite(bool status){
    //iterate through every locations in board and when encounters a white piece, set the underThreat value according to piece
    for(int row = 0; row <= 7; row++){
        for(int col = 0; col <= 7; col++){
            switch(board[row][col].getName()){
                case 'P':
                    setThreatPawn(row, col, status);
                    break;
                case 'R':
                    setThreatRook(row, col, status);
                    break;
                case 'N':
                    setThreatKnight(row, col, status);
                    break;
                case 'B':
                    setThreatBishop(row, col, status);
                    break;
                case 'Q':
                    setThreatQueen(row, col, status);
                    break;
                case 'K':
                    setThreatKing(row, col, status);
                    break;  
            }
        }
    }
}

void ChessBoard:: checkUnderThreatBlack(bool status){
    //iterate through every locations in board and when encounters a black piece, set the underThreat value according to piece
    for(int row = 0; row <= 7; row++){
        for(int col = 0; col <= 7; col++){
            switch(board[row][col].getName()){
                case 'p':
                    setThreatPawn(row, col, status);
                    break;
                case 'r':
                    setThreatRook(row, col, status);
                    break;
                case 'n':
                    setThreatKnight(row, col, status);
                    break;
                case 'b':
                    setThreatBishop(row, col, status);
                    break;
                case 'q':
                    setThreatQueen(row, col, status);
                    break;
                case 'k':
                    setThreatKing(row, col, status);
                    break;  
            }
        }
    }
}

void ChessBoard::checkUnderThreat(bool status){
    //iterate through every locations in board and when encounters a black or white piece, set the underThreat value according to piece
    for(int row = 0; row <= 7; row++){
        for(int col = 0; col <= 7; col++){
            switch(board[row][col].getName()){
                case 'P':
                case 'p':
                    setThreatPawn(row, col, status);
                    break;
                case 'R':
                case 'r':
                    setThreatRook(row, col, status);
                    break;
                case 'N':
                case 'n':
                    setThreatKnight(row, col, status);
                    break;
                case 'B':
                case 'b':
                    setThreatBishop(row, col, status);
                    break;
                case 'Q':
                case 'q':
                    setThreatQueen(row, col, status);
                    break;
                case 'K':
                case 'k':
                    setThreatKing(row, col, status);
                    break;

            }
        }
    }
}

const double ChessBoard:: calculateScoreWhite(){
    //iterate through every locations on the board,when encounters a white piece,then add its value to totalValue if it is underThreat add half of its value.
    double totalPieceValue = 0.0;
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            if(board[i][j].getName() >= 'A' && board[i][j].getName() <= 'Z'){
                if(board[i][j].getunderThreatBlack()){
                    totalPieceValue += (board[i][j].getValue() / 2.0);
                }else{
                    totalPieceValue += board[i][j].getValue();
                }
            }
        }
    }
    return totalPieceValue;
}

const double ChessBoard:: calculateScoreBlack(){
    //iterate through every locations on the board,when encounters a black piece,then add its value to totalValue if it is underThreat add half of its value.
    double totalPieceValue = 0.0;
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            if(board[i][j].getName() >= 'a' && board[i][j].getName() <= 'z'){
                if(board[i][j].getunderThreatWhite()){
                    totalPieceValue += (board[i][j].getValue() / 2.0);
                }else{
                    totalPieceValue += board[i][j].getValue();
                }
            }
        }
    }
    return totalPieceValue;
}

void ChessBoard ::printScore(){
    //Prints the scores of white and black.
    cout << "White Score: " << calculateScoreWhite() << endl;
    cout << "Black Score: " << calculateScoreBlack() << endl;
}

bool ChessBoard :: isOverride(const char pieceName){
    //checks if final position is occupied by same color piece to prevent override situation.
    if(moveCounter % 2 == 1){
        if(pieceName == 'p' || pieceName == 'r' || pieceName == 'n'||pieceName == 'b'|| pieceName == 'q'||pieceName == 'k'){
            return true;
        }else{
            return false;
        }
    }else if(moveCounter % 2 == 0){
        if(pieceName == 'P' || pieceName == 'R' || pieceName == 'N'||pieceName == 'B'|| pieceName == 'Q'||pieceName == 'K'){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool ChessBoard:: isCheck(const int beginRow,const int beginCol,const int finalRow,const int finalCol){
    int kingRow, kingCol;
    char temp = board[finalRow][finalCol].getName();

    // Find the king position according to who will play current round.
    if(moveCounter % 2 == 0){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j].getName() == 'K'){
                    kingRow = i;
                    kingCol = j;
                }
            }
        }
        //If at the begining king is underThreat by white then initially make the move and set the black threats.
        //Still white king is underThreat by black then this move is illegal because king is checked.White must protect its king.
        //Then,the temporary moved reversed.
        if(board[kingRow][kingCol].getunderThreatBlack()){
            board[finalRow][finalCol].setName(board[beginRow][beginCol].getName());
            board[beginRow][beginCol].setName('.');

            checkUnderThreatBlack(true);

            if(board[kingRow][kingCol].getunderThreatBlack()){
                board[beginRow][beginCol].setName(board[finalRow][finalCol].getName());
                board[finalRow][finalCol].setName(temp);
                cerr<< "ERROR!The opponent is checked you.You must protect your king.";
                return false;
            }else{
                board[beginRow][beginCol].setName(board[finalRow][finalCol].getName());
                board[finalRow][finalCol].setName(temp);
                return true;
            }
        }else{
            return true;
        }
    }else if(moveCounter % 2 == 1){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j].getName() == 'k'){
                    kingRow = i;
                    kingCol = j;
                }
            }
        }
        //If at the begining king is underThreat by white then initially make the move and set the white threats.
        //Still black king is underThreat by white then this move is illegal because king is checked.Black must protect its king.
        //Then,the temporary moved reversed.
        if(board[kingRow][kingCol].getunderThreatWhite()){
            board[finalRow][finalCol].setName(board[beginRow][beginCol].getName());
            board[beginRow][beginCol].setName('.');

            checkUnderThreatWhite(true);

            if(board[kingRow][kingCol].getunderThreatWhite()){
                board[beginRow][beginCol].setName(board[finalRow][finalCol].getName());
                board[finalRow][finalCol].setName(temp);
                cerr<< "ERROR!The opponent is checked you.You must move your king.";
                return false;
            }else{
                board[beginRow][beginCol].setName(board[finalRow][finalCol].getName());
                board[finalRow][finalCol].setName(temp);
                return true;
            }
        }else{
            return true;
        }
    }
    return true;
}

bool ChessBoard:: controlMoveVertical(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    bool isPathClear = true;
    bool result = false;
    //Checks the squares between begining and final locations to ensure path is clear to make move on same column.
    int less = (finalRow > beginRow) ? beginRow : finalRow;
    int more = (beginRow > finalRow) ? beginRow : finalRow;
    for(int i = less + 1; i <= more - 1; i++){
       if(board[i][beginCol].getName() != '.'){
            isPathClear = 0;
            break;
        }
    }
    //If path clear,then control the player is checked, if user didnt checked or get rid of check situation.
    if(isPathClear){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }
    
    return result;
}

bool ChessBoard:: controlMoveHorizontal(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    bool isPathClear = true;
    bool result = false;
    //Checks the squares between begining and final locations to ensure path is clear to make move on same row.
    int less = (finalCol > beginCol) ? beginCol : finalCol;
    int more = (beginCol > finalCol) ? beginCol : finalCol;
    for(int i = less + 1; i <= more - 1; i++){
        if(board[beginRow][i].getName() != '.'){
            isPathClear = false;
            break;
        }
    }
    //If path clear,then control the player is checked, if user didnt checked or get rid of check situation.
    if(isPathClear){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }
    
    return result;
}

bool ChessBoard:: controlMoveDiagonal(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    bool isPathClear = true;
    bool result = false;
    //Checks the squares between begining and final locations to ensure path is clear to make move on diagonal.
    int rowStep = (finalRow > beginRow) ? 1 : -1;
    int colStep = (finalCol > beginCol) ? 1 : -1;
    for (int i = 1; i < abs(finalRow - beginRow); i++) {
        if (board[beginRow + i * rowStep][beginCol + i * colStep].getName() != '.') {
            isPathClear = false;
            break;
        }
    }
    //If path clear,then control the player is checked, if user didnt checked or get rid of check situation.
    if(isPathClear){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }
    
    return result;   
}


bool ChessBoard :: movePawn(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    
    int direction = (moveCounter % 2 == 0) ? 1 : -1;
    bool result = false;
    //Checks direction is correct for pawn according to color.Pawn must not backwards.
    if((direction == 1 && finalRow-beginRow < 0) || (direction == -1 && finalRow-beginRow > 0)){
        cerr << "ERROR! Invalid pawn move direction.";
        return false;
    }
    //Control moves(initial 2 square ahead move, 1 square ahead move, 1 square diagonal capture move)
    if(abs(finalCol - beginCol) == 0 && abs(finalRow - beginRow) == 2 && ((beginRow == 1 && direction == 1) || (beginRow == 6 && direction == -1))){
        // Check if the path is clear
        if(board[beginRow + direction][finalCol].getName() == '.' && board[finalRow][finalCol].getName() == '.'){
            result = isCheck(beginRow, beginCol, finalRow, finalCol);
        }
    }else if(finalCol == beginCol && abs(finalRow - beginRow) == 1 && board[finalRow][finalCol].getName() == '.'){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }else if(abs(finalCol - beginCol) == 1 && abs(finalRow - beginRow) == 1 && board[finalRow][finalCol].getName() != '.'){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }
    //Checks override situation.
    if(isOverride(board[finalRow][finalCol].getName())){
        cerr << "ERROR!You are trying put a piece over a your own piece.";
        return false;
    }
    //If move is legal,then removes the underThreat values from previous locations.
    if(result){
        setThreatPawn(beginRow,beginCol,false);
        return result;
    }
        
    cerr << "ERROR!Invalid move.";
    return false;
}

bool ChessBoard :: moveRook(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    bool result = false;
    //Checks override situation.
    if(isOverride(board[finalRow][finalCol].getName())){
        cerr << "ERROR!You are trying put a piece over a your own piece.";
        return false;
    }
    //Checks horizontal and vertical moves.
    if(finalRow == beginRow){
        result = controlMoveHorizontal(beginRow, beginCol, finalRow, finalCol);
    }else if(finalCol == beginCol){
        result = controlMoveVertical(beginRow, beginCol, finalRow, finalCol);
    }
    //If move is legal,then removes the underThreat values from previous locations.
    if(result){
        setThreatRook(beginRow,beginCol,false);
        return result;
    }

    cerr << "ERROR!Invalid move.";
    return false;
}


bool ChessBoard :: moveKnight(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    //Checks override situation.
    if(isOverride(board[finalRow][finalCol].getName())){
        cerr << "ERROR!You are trying put a piece over a your own piece.";
        return false;
    }
    //Checks knight moves.
    bool result = false;
    if(abs(finalRow - beginRow) == 1 && abs(finalCol - beginCol) == 2){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }else if(abs(finalRow - beginRow) == 2 && abs(finalCol - beginCol) == 1){
        result = isCheck(beginRow, beginCol, finalRow, finalCol);
    }
    //If move is legal,then removes the underThreat values from previous locations.
    if(result){
        setThreatKnight(beginRow, beginCol, false);
        return result;
    }

    cerr << "ERROR!Invalid knight move.";
    return false;
}

bool ChessBoard :: moveBishop(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    //Checks override situation.
    if(isOverride(board[finalRow][finalCol].getName())){
        cerr << "ERROR!You are trying put a piece over a your own piece.";
        return false;
    }
    //Checks diagonal moves.
    bool result = false;
    if(abs(finalRow - beginRow) == abs(finalCol - beginCol)){
        result = controlMoveDiagonal(beginRow, beginCol, finalRow, finalCol);
    }     
    //If move is legal,then removes the underThreat values from previous locations.
    if(result){
        setThreatBishop(beginRow, beginCol, false);
        return result;
    }

    cerr << "ERROR!Invalid move.";
    return false;
}

bool ChessBoard :: moveQueen(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    //Checks override situation.
    if(isOverride(board[finalRow][finalCol].getName())){
        cerr << "ERROR!You are trying put a piece over a your own piece.";
        return false;
    }
    //Checks horizontal,vertical and diagonal moves.
    bool result = false;
    if(abs(finalRow - beginRow) == abs(finalCol - beginCol)){
        result = controlMoveDiagonal(beginRow, beginCol, finalRow, finalCol);
    }else if(finalRow == beginRow){
        result = controlMoveHorizontal(beginRow, beginCol, finalRow, finalCol);
    }else if(finalCol == beginCol){
        result = controlMoveVertical(beginRow, beginCol, finalRow, finalCol);
    }     
    //If move is legal,then removes the underThreat values from previous locations.
    if(result){
        setThreatQueen(beginRow, beginCol, false);
        return result;
    }

    cerr << "ERROR!Invalid move.";
    return false;
}

bool ChessBoard :: moveKing(const int& beginRow,const int& beginCol,const int& finalRow,const int& finalCol){
    //Checks override situation.
    if(isOverride(board[finalRow][finalCol].getName())){
        cerr << "ERROR!You are trying put a piece over a your own piece.";
        return false;
    }
    //Checks the final location is underThreat by opponent,if it is underThreat,then it is not allowed cannot put king to underThreat position.
    bool underThreat;
    bool result = false;
    if(board[beginRow][beginCol].getName() == 'k')
        underThreat = board[finalRow][finalCol].getunderThreatWhite();
    else if(board[beginRow][beginCol].getName() == 'K')
        underThreat = board[finalRow][finalCol].getunderThreatBlack();  
    //Checks the 1 square horizontal,vertical and diagonal moves of king.
    if(underThreat == false){
        if(finalRow == beginRow && abs(finalCol - beginCol) == 1){
            result = isCheck(beginRow, beginCol, finalRow, finalCol);
        }else if(finalCol == beginCol && abs(finalRow - beginRow) == 1){
            result = isCheck(beginRow, beginCol, finalRow, finalCol);
        }else if(abs(finalRow - beginRow) == 1 && abs(finalCol - beginCol) == 1){
            result = isCheck(beginRow, beginCol, finalRow, finalCol);
        }     
    }else{
        cerr << "The selected location is under threat.";
        return false;
    }
    //If move is legal,then removes the underThreat values from previous locations.
    if(result){
        setThreatKing(beginRow, beginCol, false);
        return result;
    }
    
    cerr << "ERROR!Invalid move.";
    return false;
}

bool ChessBoard::checkMoveValidatiy(const int beginRow,const int beginCol,const int finalRow,const int finalCol){
    //Player cannot move a empty position or cannot put the selected piece at the same position or cannot play opponent's piece.
    bool valid = false;
    if(board[beginRow][beginCol].getName() == '.'){
        cerr << "ERROR!There is not a piece in the selected coordinates.";
        return false;
    }

    if(beginRow == finalRow && beginCol == finalCol){
        cerr<< "ERROR!You are already at the selected location.";
        return false;
    }

    if((moveCounter % 2 == 0) && (board[beginRow][beginCol].getName() >= 'a' && board[beginRow][beginCol].getName() <= 'z')) {
        cerr << "ERROR!You cannot move black pieces as white.";
        return false;
    }else if((moveCounter % 2 == 1) && (board[beginRow][beginCol].getName() >= 'A' && board[beginRow][beginCol].getName() <= 'Z')){
        cerr << "ERROR!You cannot move white pieces as black.";
        return false;
    }
    //According to type of the piece in the selected position, calls necesarry move function.
    switch(board[beginRow][beginCol].getName()){
        case 'p':
        case 'P':
            valid = movePawn(beginRow, beginCol, finalRow, finalCol);
            break;
        case 'r':
        case 'R':
            valid = moveRook(beginRow, beginCol, finalRow, finalCol);
            break;
        case 'n':
        case 'N':
            valid = moveKnight(beginRow, beginCol, finalRow, finalCol);
            break;
        case 'b':
        case 'B':
            valid = moveBishop(beginRow, beginCol, finalRow, finalCol);
            break;
        case 'q':
        case 'Q':
            valid = moveQueen(beginRow, beginCol, finalRow, finalCol);
            break;
        case 'k':
        case 'K':
            valid = moveKing(beginRow, beginCol, finalRow, finalCol);
            break;
    }
    //Then it returns validity of move.
    return valid;
}

void ChessBoard :: updateBoard(string& input){
    //If user writes score,then prints the scores of white and black.
    if(input == "score"){
        printScore();
    }else if((input.length() == 4)){
        //Checks the input string,if it is in correct form and boundaries is correct,then checks the move's validity.
        int beginCol = static_cast<int>(input[0]) - static_cast<int>('a');
        int finalCol = static_cast<int>(input[2]) - static_cast<int>('a');
        int beginRow = static_cast<int>(input[1]) - static_cast<int>('1');
        int finalRow = static_cast<int>(input[3]) - static_cast<int>('1');

        //If move valid,then piece is moved to selected position.
        if(beginCol >= 0 && beginCol <= 7 && finalCol >= 0 && finalCol <= 7 &&  beginRow >= 0 && beginRow <= 7 && finalRow >= 0 && finalRow <= 7){
            if(checkMoveValidatiy(beginRow, beginCol, finalRow, finalCol)){
                board[finalRow][finalCol].setName(board[beginRow][beginCol].getName());
                board[beginRow][beginCol].setName('.');
                board[finalRow][finalCol].setValue(board[beginRow][beginCol].getValue());
                board[beginRow][beginCol].setValue(0.0);

                checkUnderThreat(true); //The new threated locations is determined.
                ++moveCounter; // moveCounter is increased to track the turns between players.

                cout << "[Updated Board]" << endl;
            }else{
                cerr << "Make a legal move." << endl;
            }

        }else{
            cerr << "ERROR! Be careful about boundaries of board.You must enter 1 to 8 for rows and 'a' to 'h' for columns" << endl;
        }

    }else{
        cerr << "ERROR! You didnt enter a valid chess input for example 'e2e4'"<< endl;
    }

}

void ChessBoard :: takeInput(){
    string input;
    //If it is first move,then board is initialized and game begins.
    if(!(firstMove)){   
        cout << "Welcome to the Chess Game! " << endl;
        initializeBoard();
        printBoard();    
        setFirstMove(true);
    }
    //According to the turns,move input is wanted from each player.According to move.necesarry update is made on board and board printed.
    if(moveCounter % 2 == 0){
        cout << "[White's Turn]" << endl << "Enter your move: ";
        cin >> input;

        updateBoard(input);
        printBoard();
    }else if(moveCounter % 2 == 1){
        cout << "[Black's Turn]" << endl << "Enter your move: ";
        cin >> input;

        updateBoard(input);
        printBoard();
    }

}

bool ChessBoard::getunderThreat(const int& beginRow,const int& beginCol,const int& nextRow,const int& nextCol){
    //Get the underThreat values of the piece by opponent.
    if(board[beginRow][beginCol].getName() >= 'a' && board[beginRow][beginCol].getName() <= 'z')
        return board[nextRow][nextCol].getunderThreatWhite();
    else if(board[beginRow][beginCol].getName() >= 'A' && board[beginRow][beginCol].getName() <= 'Z')
        return board[nextRow][nextCol].getunderThreatBlack();

    return false;
}

bool ChessBoard::isKingMoveable(int row, int col){
    //If the possible locations of king's move is not overridden or not underThreat by opponent,then king is moveable.
    for(int i = row - 1; i <= row + 1; ++i){
        for(int j = col - 1; j <= col + 1; ++j){
            if(i >= 0 && i <= 7 && j >= 0 && j <= 7 && (i != row || j != col)){
                // Check if the square is not overridden by the same color
                if(!isOverride(board[i][j].getName())){
                    // Check if the square is not underThreat
                    if(!getunderThreat(row, col, i, j)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isGameFinished(){
    //If player's king is underThreat by opponent and king is not moveable then game finished.
    char kingSymbol = (moveCounter % 2 == 0) ? 'K' : 'k';
    for(int i = 0; i <= 7; ++i){
        for(int j = 0; j <= 7; ++j){
            if(board[i][j].getName() == kingSymbol){
                // Check if the king is under threat
                if((moveCounter % 2 == 0 && board[i][j].getunderThreatBlack()) ||
                    (moveCounter % 2 == 1 && board[i][j].getunderThreatWhite())){
                    // Check if the king has no available moves
                    if (!isKingMoveable(i, j)) {
                        return true;  // Checkmate
                    }
                }
                break;
            }
        }
    }
    return false;
}   

void ChessBoard :: saveMovesFile(ofstream& fout) const{
    //The legal moves that made by users is printed to a txt file.
    if(moveCounter % 2 == 1)
        fout << "[White's Turn]" << endl;
    else if(moveCounter % 2 == 0)
        fout << "[Black's Turn]" << endl;

    for(int i=7; i >= 0; --i){
    	fout << i+1 << "  |  ";  
		for(int j=0; j <= 7; ++j){
            fout<<board[i][j] << "  ";
        }
        fout << endl;
    }

    fout << "    -------------------------" << endl;
    fout << "    " << "  a  " << "b  " << "c  " << "d  "<< "e  "<< "f  "<< "g  "<< "h  " << endl;

}

void ChessBoard:: playGame(){
    ofstream fout;
    fout.open("game.txt");

    int oldCount = moveCounter;
    //Until the gameFinised,game keeps taking input from users.
    while(!(isGameFinished())){
        takeInput();
        if(moveCounter != oldCount){
            saveMovesFile(fout);  //IF a move is made, it is printed to game.txt.
            oldCount = moveCounter;
        }
    }
    //The winner player is printed to both terminal and game.txt.
    if(moveCounter % 2 == 1){
        cout << "WHITE WON!" << endl;
        fout << "WHITE WON!" << endl;
    }else if(moveCounter % 2 == 0){
        cout << "BLACK WON!" << endl;
        fout << "BLACK WON!" << endl;
    }

    fout.close();
}


