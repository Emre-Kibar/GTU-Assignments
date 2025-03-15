all: compile run clean

compile: main.cpp myShell.h myShell.cpp file.h file.cpp directory.h directory.cpp regularFile.h regularFile.cpp softLinkedFile.h softLinkedFile.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 main.cpp myShell.cpp file.cpp directory.cpp regularFile.cpp softLinkedFile.cpp -o myOS

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	
	@echo "==========================================="
	@./myOS
	@echo "==========================================="

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f myOS