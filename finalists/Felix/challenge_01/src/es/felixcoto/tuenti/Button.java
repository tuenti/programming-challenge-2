package es.felixcoto.tuenti;

import java.util.HashMap;
import java.util.Map;
/**
 * Enum type used to store button properties
 * @author Felix
 *
 */
public enum Button {
	BUTTON_1(0,0,new char[]{' ','1'}),
	BUTTON_2(1,0,new char[]{'a','b','c','2'}),
	BUTTON_3(2,0,new char[]{'d','e','f','3'}),
	BUTTON_4(0,1,new char[]{'g','h','i','4'}),
	BUTTON_5(1,1,new char[]{'j','k','l','5'}),
	BUTTON_6(2,1,new char[]{'m','n','o','6'}),
	BUTTON_7(0,2,new char[]{'p','q','r','s','7'}),
	BUTTON_8(1,2,new char[]{'t','u','v','8'}),
	BUTTON_9(2,2,new char[]{'w','x','y','z','9'}),
	BUTTON_0(1,3,new char[]{'0'}),
	BUTTON_UP(2,3,new char[]{});
	
	
	private final int horizontalPosition;
	private final int verticalPosition;
	private final char[] characterOrder;
	private final Map<Character, Integer> numPushForChar;
	
	private static Map<Character,Button> buttonForChar=new HashMap<Character, Button>();
	
	
	Button(int horizontalPosition,int verticalPosition,char[] characterOrder){
		this.horizontalPosition=horizontalPosition;
		this.verticalPosition=verticalPosition;
		this.characterOrder=characterOrder;
		this.numPushForChar=new HashMap<Character, Integer>();
		for (int i=0;i<characterOrder.length;i++){
			char currentCharacter=characterOrder[i];
			this.numPushForChar.put(currentCharacter, i+1);
			if (Character.isLetter(currentCharacter)){
				this.numPushForChar.put(Character.toUpperCase(currentCharacter), i+1);	
			}
		}
	}

	public int getHorizontalPosition() {
		return horizontalPosition;
	}

	public int getVerticalPosition() {
		return verticalPosition;
	}

	public char[] getCharacterOrder() {
		return characterOrder;
	}

	public int getNumOfPush(char character) {
		return numPushForChar.get(character);
	}
	
	public static Button getButtonForChar(char character){
		if (buttonForChar.isEmpty()){
			initializeMap();
		}
		return buttonForChar.get(character);
	}

	private static void initializeMap() {
		for (Button currentButton : Button.values()) {
			for (char currentCharacter:currentButton.characterOrder){
				buttonForChar.put(currentCharacter, currentButton);
				if (Character.isLetter(currentCharacter)){
					buttonForChar.put(Character.toUpperCase(currentCharacter), currentButton);
				}

			}
		}
		
	}
	
	
}
