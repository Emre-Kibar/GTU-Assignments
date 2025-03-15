JC = javac
JFLAGS = -g
TARGET = tester
SOURCES = tester.java SortAlgorithm.java BubbleSort.java MergeSort.java QuickSort.java SelectionSort.java


default: $(TARGET)

$(TARGET): $(SOURCES)
	$(JC) $(JFLAGS) $^
	java $(TARGET)


clean:
	rm -f *.class

.PHONY: clean default