all: compile run clean

compile: 
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@javac *.java 

doc:	
	@echo "-------------------------------------------"
	@echo "Creating java documentation..."
	@javadoc -d docs *.java

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	
	@echo "==========================================="
	@java Main
	@echo "==========================================="

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.class

cleandoc:
	@echo "-------------------------------------------"
	@echo "Cleaning java documentation..."
	@rm -rf docs