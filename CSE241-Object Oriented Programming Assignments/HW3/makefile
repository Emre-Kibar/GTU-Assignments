all: compile run clean

compile: 

	@echo "-------------------------------------------"
	@echo "Compiling..."
	@javac myInterface/*.java mySource/*.java JavaContainerTest.java 

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	
	@echo "==========================================="
	@java JavaContainerTest
	@echo "==========================================="

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.class
	@rm -f myInterface/*.class
	@rm -f mySource/*.class