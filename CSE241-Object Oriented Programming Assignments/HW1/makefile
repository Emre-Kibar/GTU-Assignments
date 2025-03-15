all: compile run clean

compile: main.cpp Chess_Board.h Chess_Board.cpp Chess_Pieces.h Chess_Pieces.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ main.cpp Chess_Board.cpp Chess_Pieces.cpp -o ChessGame

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	
	@echo "==========================================="
	@./ChessGame
	@echo "==========================================="

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f ChessGame