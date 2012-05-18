package es.felixcoto.tuenti;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class PasswordSolver {
	
	
	LetterPosition objRoot=new LetterPosition('^');
	Map<Character, LetterPosition> objMapLetters=new HashMap<Character, LetterPosition>();
	
	
	public void processLetterOrder(char firstLetter,char secondLetter){
		LetterPosition objLetterPositionFirst=getLetterPosition(firstLetter);
		LetterPosition objLetterPositionSecond=getLetterPosition(secondLetter);
		objLetterPositionFirst.adoptAsImmediateSuccesor(objLetterPositionSecond);
	}


	private LetterPosition getLetterPosition(char letter) {
		LetterPosition objResult;
		if (objMapLetters.containsKey(letter)){
			objResult=objMapLetters.get(letter);
		}else{
			objResult=new LetterPosition(letter);
			objMapLetters.put(letter, objResult);
			objRoot.adoptAsImmediateSuccesor(objResult);
		}
		return objResult;
	}
	
	
	
	public List<String> getPosiblePasswords(){
		List<String> objPosiblePasswords=new ArrayList<String>();
		// Initialize with empty password
		objPosiblePasswords.add("");
		for (int i=0;i<objMapLetters.size();i++){
			List<String> objNewPosiblePasswords=new ArrayList<String>();
			//Iterate for every posible password
			for (String objOldPassword : objPosiblePasswords) {
				Set<LetterPosition> addedLetters=new HashSet<LetterPosition>();
				Set<LetterPosition> possibleLetters=new HashSet<LetterPosition>();
				// Add root successors and add Root as added letter
				possibleLetters.addAll(objRoot.getImmediateSuccessors());
				addedLetters.add(objRoot);
				// Iterate for every letter of current password to explore next letters 
				for (int j=0;j<objOldPassword.length();j++){
					LetterPosition objAddedLetter=objMapLetters.get(objOldPassword.charAt(j));
					possibleLetters.addAll(objAddedLetter.getImmediateSuccessors());
					addedLetters.add(objAddedLetter);
				}
				// Remove added letters
				possibleLetters.removeAll(addedLetters);
				for (LetterPosition objLetterPosition : possibleLetters) {
					// Check if all predecessors are already added
					if (addedLetters.containsAll(objLetterPosition.getPredecesors())){
						StringBuilder sb=new StringBuilder();
						sb.append(objOldPassword);
						sb.append(objLetterPosition.getCharacter());
						objNewPosiblePasswords.add(sb.toString());
					}
				}
				
				
			}
			objPosiblePasswords=objNewPosiblePasswords;
		}
		return objPosiblePasswords;
	}
	
	

}

class LetterPosition{
	private final char character;
	private Set<LetterPosition> objSetPredecessors;
	private Set<LetterPosition> objSetSuccesors;
	private Set<LetterPosition> objSetImmediateSuccesors;
	
	/**
	 * @param objCCaracter
	 */
	public LetterPosition(char character) {
		this.character = character;
		objSetPredecessors=new HashSet<LetterPosition>();
		objSetSuccesors=new HashSet<LetterPosition>();
		objSetImmediateSuccesors=new HashSet<LetterPosition>();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + character;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		LetterPosition other = (LetterPosition) obj;
		if (character != other.character)
			return false;
		return true;
	}
	
	private void adoptAsDistantSuccessor(LetterPosition objNewLetterPosition){
		objNewLetterPosition.adoptAsPredecessor(this);
		objSetImmediateSuccesors.remove(objNewLetterPosition);
		objSetSuccesors.add(objNewLetterPosition);
		objSetSuccesors.addAll(objNewLetterPosition.getSuccesors());
	}

	private void adoptAsPredecessor(LetterPosition objPredecessor) {
		this.objSetPredecessors.add(objPredecessor);
	}
	
	protected void adoptAsImmediateSuccesor(LetterPosition objImmediateSuccesor){
		if (!objSetSuccesors.contains(objImmediateSuccesor)){
			objSetSuccesors.add(objImmediateSuccesor);
			objSetSuccesors.addAll(objImmediateSuccesor.getSuccesors());
			objSetImmediateSuccesors.add(objImmediateSuccesor);
			objImmediateSuccesor.adoptAsPredecessor(this);
			for (LetterPosition objPredecessor : objSetPredecessors) {
				objPredecessor.adoptAsDistantSuccessor(objImmediateSuccesor);
			}
		}
	}
	
	protected Set<LetterPosition> getImmediateSuccessors(){
		return objSetImmediateSuccesors;
	}

	@Override
	public String toString() {
		return String.format("LetterPosition [cCharacter=%s]", character);
	}

	public char getCharacter() {
		return character;
	}
	
	
	private Set<LetterPosition> getSuccesors(){
		return objSetSuccesors;
	}
	
	protected Set<LetterPosition> getPredecesors(){
		return objSetPredecessors;
	}
}