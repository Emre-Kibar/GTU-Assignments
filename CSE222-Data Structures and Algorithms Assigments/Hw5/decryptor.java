import java.util.Map;
import java.util.Iterator;

public class decryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text = "";
	private String cipher_text;
	
	public decryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		// Assign the arguments to member variables.
		map = _map;
		cipher_text = text;
		key = _key;
	}

	public void decrypt() {
		// do not edit this method
		generate_keystream();
		generate_plain_text();
	}
	
	private void generate_keystream() {
		if(cipher_text.length() <= key.length()){ // if the key length is greater or equal than cipher_text,then key must parse with cipher_text.length.
			keystream = key.substring(0, cipher_text.length());
		}else{
			//if the cipher_text has greater length than key,then I am converting this case to initial case by adding key at the end within the loop
			//until key has greater length than cipher_text,then again parse the key with the length of cipher_text
			StringBuilder tempKey = new StringBuilder(key);
			while(tempKey.length() < cipher_text.length()){
				tempKey.append(key);
			}
			keystream = tempKey.substring(0, cipher_text.length());
		}
	}
	
	private void generate_plain_text() {
	// You must use map.get(x).keySet() with an iterator in this method

		StringBuilder plainText = new StringBuilder();	// plainText will store the the value to assign to plain_text. 

		for(int i = 0; i < keystream.length(); i++){ // By iterating through the keystream and cipher_text characters,we will get the column and intersection character.
			char keyStreamChar = keystream.charAt(i);
			char cipherTextChar = cipher_text.charAt(i);

			Iterator<Character> rowIterator = map.keySet().iterator(); // rowIterator will used to iterate over rows of the map.
			while(rowIterator.hasNext()){
				char plainTextChar; // The correct rowChar will be stored as plainTextChar.
				boolean isPlTextChFound = false;	// The state of plainTextChar is controled by isPlTextChFound.

				char rowChar = rowIterator.next(); // rowChar will be stored with the value from rowIterator.
				Iterator<Character> colIterator = map.get(rowChar).keySet().iterator(); // colIterator will be used to iterate over the columns of selected row.
				
				while(colIterator.hasNext()){
					char colChar = colIterator.next(); // colChar will be stored with the value from colIterator. 
					char intersectionChar = map.get(rowChar).get(colChar); // The intersection of selected row and column will be assigned to intersectionChar.

					// If the colChar and intersectionChar validate the values that comes from keystream(column value) and cipher_text(intersection value),
					// then it means this innerMap's row value will be the plainTextChar.
					if(colChar == keyStreamChar && intersectionChar == cipherTextChar){
						// If conditions is true then plainTextChar is found and appened to plainText.
						plainTextChar = rowChar; 
						isPlTextChFound = true; 
						plainText.append(plainTextChar);
						break; //If plaintext character is found then no need to continue to iterate columns.
					}
				}

				if(isPlTextChFound){ // If plaintext character is found then no need to continue to iterate rows.
					break;
				}
			}
		}

		plain_text = plainText.toString(); // plainText is assigned to plain_text to be stored
	}

	public String get_keystream() {
		return keystream;	//Returns keystream string.
	}
	
	public String get_plain_text() {
		return plain_text;	//Returns plain_text string.
	}
}
