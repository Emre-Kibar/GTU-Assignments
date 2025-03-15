import java.util.HashMap;
import java.util.Map;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.Iterator;

public class alphabet {
	private Set<Character> english_alphabet = new LinkedHashSet<Character>();
	private Map<Character, Map<Character, Character>> map = new HashMap<Character,  Map<Character, Character>>();
	
	public alphabet() {
		// do not edit this method
		fill_english_alphabet();
		fill_map();
	}
	
	private void fill_english_alphabet() {
		// do not edit this method
		for(char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()) {
		    english_alphabet.add(c);
		}
	}
	
	private void fill_map() {
	// You must use the "english_alphabet" variable in this method, to fill the "map" variable.
	// You can define 1 or 2 iterators to iterate through the set items.

		Iterator<Character> rowIter= english_alphabet.iterator(); // rowIter will be used to iterate the alphabet for row values.
		Iterator<Character> colIter; // colIter will be used to iterate the alphabet for column values.

		int rowCount = 0; // rowCount will hold the count of processed rows. 		
		while(rowIter.hasNext()){  // By using this loop, rows will be iterated.
			char rowCharacter = rowIter.next(); // The next value of row will be assigned to rowCharacter. 
			
			Map<Character, Character> innerMap = new HashMap<>(); // innerMap created to hold the value of outer map.
			colIter = english_alphabet.iterator(); //colIter will be reseted every row.
			int colCount = 0; // colCount will be hold the count of processed columns. 

			while(colIter.hasNext()){ // By using this loop, columns will be iterated. 
				char colCharacter = colIter.next(); // The next value of column will be assigned to colCharacter.
				char intersectionChar = (char)('A' + (rowCount + colCount) % 26); // Correct intersectionChar is calculated using rowCount and colCount.
				innerMap.put(colCharacter, intersectionChar); // The relevant column and intersection is mapped within the innerMap.
				colCount++; // After each column is processed, the colCount is incremented.
			}

			map.put(rowCharacter, innerMap); // The relevant row and innerMap is mapped wihtin the outerMap.
			rowCount++; // After each row is processed, the rowCount is incremented.
		}
	}

	public void print_map() {
		// do not edit this method
		System.out.println("*** Viegenere Cipher ***\n\n");
		System.out.println("    " + english_alphabet);
		System.out.print("    ------------------------------------------------------------------------------");
		for(Character k: map.keySet()) {
			System.out.print("\n" + k + " | ");
			System.out.print(map.get(k).values());
		}
		System.out.println("\n");
		
	}

	public Map get_map() {
		return map; // return the map that holds vigenere cipher.
	}
}