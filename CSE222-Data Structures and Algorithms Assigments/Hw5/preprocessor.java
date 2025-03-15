public class preprocessor {
	private String initial_string;
	private String preprocessed_string;
		
	public preprocessor(String str) {
		// initial_String is stored and preprocessed_string is initialized as empty string.
		initial_string = str;
		preprocessed_string = "";
	}

	public void preprocess() {
		// do not edit this method
		capitalize();
		clean();
	}
	
	private void capitalize() {
		StringBuilder capitalizedString = new StringBuilder(); // capitalized string is the intial_string with all letter is capital letter. 
		// iterating over initial_string characters one by one
		for(int i=0; i<initial_string.length(); i++){ 
            char currentChar = initial_string.charAt(i); // keeping the current character in the loop
            
			// Check if the currentChar is letter,then make the character upperCase letter else keep the non-letter character 
            if(Character.isLetter(currentChar)){ 
                capitalizedString.append(Character.toUpperCase(currentChar));
            }else{
                capitalizedString.append(currentChar);
            }
        }
        initial_string = capitalizedString.toString(); // initial_string's letters is upperCase now.
	}

	private void clean() {
		preprocessed_string = initial_string.replaceAll("[^A-Z]", ""); // replace all non-upperCase letters with empty string 
	}
	
	public String get_preprocessed_string() {
		return preprocessed_string; // Returns the preprocessed_string.
	}
}