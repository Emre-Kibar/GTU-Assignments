import java.util.Map;

public class encryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text;
	private String cipher_text = "";
	
	public encryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		// Assign the parameters to the member variables
		map = _map;
		plain_text = text;
		key = _key;
	}
	
	public void encrypt() {
		// do not edit this method
		generate_keystream();
		generate_cipher_text();
	}
	
	private void generate_keystream() {
		if(plain_text.length() <= key.length()){	// if the key length is greater or equal than plain_text,then key must be parsed with plain_text.length.
			keystream = key.substring(0, plain_text.length());
		}else{	
			//if the plain_text has greater length than key,then I am converting this case to initial case by adding key at the end within the loop
			//until key has greater length than plain_text,then again parse the key with the length of plain_text
			StringBuilder tempKey = new StringBuilder(key);
			while(tempKey.length() < plain_text.length()){
				tempKey.append(key);
			}
			keystream = tempKey.substring(0, plain_text.length());
		}
	}
	
	private void generate_cipher_text() {
		StringBuilder cipherText = new StringBuilder(); //cipherText variable will hold the string which will represent cipher_text

		// By iterating through the characters within plain_text and keystream,we get the row and column characters.
		for(int i = 0; i < keystream.length(); i++){
			char plainTextChar = plain_text.charAt(i);
			char keyStreamChar = keystream.charAt(i);

			//After we found row and column characters,their intersection character will be appended to cipherText.
			char intersectionChar = map.get(plainTextChar).get(keyStreamChar);
			cipherText.append(intersectionChar);
		}

		cipher_text = cipherText.toString();  // After the loop, cipherText string will be assigned to cipher_text to store.
	}

	public String get_keystream() {
		return keystream;	// Returns keystream string.
	}
	
	public String get_cipher_text() {
		return cipher_text;	   //Returns cipher_text string.
	}
}
