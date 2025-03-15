import java.util.Map;
import java.util.Scanner;

public class tester {
	
	// *** do not change anything in this file ***
	
	public static void main(String[] args) {
		// generating and printing the map
		alphabet a = new alphabet();
		a.print_map();
		Map<Character,  Map<Character, Character>> map = a.get_map();
		
		// reading inputs
		Scanner reader = new Scanner(System.in);
		System.out.print("Text: ");
		String text = reader.nextLine();
		System.out.print("Key: ");
		String key = reader.nextLine();
		reader.close();
		
		// preprocessing the strings
		preprocessor prep = new preprocessor(text);
		prep.preprocess();
		text = prep.get_preprocessed_string();
		
		prep = new preprocessor(key);
		prep.preprocess();
		key = prep.get_preprocessed_string();
		
		// if inputs are not proper, terminate
		if (text.length() == 0 || key.length() == 0) {
			System.out.println("Given input is not proper. Please try again.");
		}
		
		// if inputs are proper, perform encryption and decryption
		else {
			
			System.out.println("\n\n**********\nPreprocessed Text: " + text);
			System.out.println("Preprocessed Key: " + key);
			
			// encryption
			encryptor e = new encryptor(map, key, text);
			e.encrypt();
			System.out.println("\n\n**********\nENCRYPTION");
			System.out.println("Plaintext: " + text);
			System.out.println("Keystream: " + e.get_keystream());
			System.out.println("Ciphertext: " + e.get_cipher_text());
			
			// decryption
			decryptor d = new decryptor(map, key, text);
			d.decrypt();
			System.out.println("\n\n**********\nDECRYPTION");
			System.out.println("Ciphertext: " + text);
			System.out.println("Keystream: " + d.get_keystream());
			System.out.println("Plaintext: " + d.get_plain_text());
		}		
	}
}