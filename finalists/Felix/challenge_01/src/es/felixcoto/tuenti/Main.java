package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	private static final int VERTICAL_DELAY=300;
	private static final int HORIZONTAL_DELAY=200;
	private static final int DIAGONAL_DELAY=350;
	private static final int PRESS_BUTTON_DELAY=100;
	private static final int DELAY_FINISH_CHARACTER=500;
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String numOfTestsString=bf.readLine();
			long numOfTests=Long.parseLong(numOfTestsString);
			long currentNumberOfTest=0;
			while (currentNumberOfTest<numOfTests){
				String currentInputTest=bf.readLine();
				long delayOfCurrentInput=calculateDelay(currentInputTest);
				System.out.println(delayOfCurrentInput);
				currentNumberOfTest++;
			}
			
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}
	
	
	
	public static long calculateDelay(String input){
		long result=0;
		Button currentButton=Button.BUTTON_0;
		boolean capsLockEnabled=false;
		boolean firstCharacter=true;
		
		int currentPosition=0;
		
		while (currentPosition<input.length()){
			char currentChar=input.charAt(currentPosition);
			boolean charIsUpperCase=Character.isUpperCase(currentChar);
			// check if need to push caps lock key
			if (Character.isLetter(currentChar)&&charIsUpperCase!=capsLockEnabled){
				if (firstCharacter){
					firstCharacter=false;
				}

				result+=calculateDelayForMove(currentButton,Button.BUTTON_UP);
				result+=PRESS_BUTTON_DELAY;
				currentButton=Button.BUTTON_UP;
				capsLockEnabled=!capsLockEnabled;
			}
			
			// find next button
			Button nextButton=Button.getButtonForChar(currentChar);
			if (nextButton!=currentButton){
				result+=calculateDelayForMove(currentButton, nextButton);
				currentButton=nextButton;
			}else{
				if (!firstCharacter){
					result+=DELAY_FINISH_CHARACTER;
				}
			}
			
			// sum number of push
			result+=currentButton.getNumOfPush(currentChar)*PRESS_BUTTON_DELAY;
			
			
			currentPosition++;
			if (firstCharacter){
				firstCharacter=false;
			}
		}
		
		
		return result;
	}



	private static int calculateDelayForMove(Button objCurrentButton, Button objDestinationButton) {
		int result=0;
		
		int currentHorizontalPosition=objCurrentButton.getHorizontalPosition();
		int currentVerticalPosition=objCurrentButton.getVerticalPosition();
		int destinationHorizontalPosition=objDestinationButton.getHorizontalPosition();
		int destinationVerticalPosition=objDestinationButton.getVerticalPosition();
		
		while (currentHorizontalPosition!=destinationHorizontalPosition ||
			   currentVerticalPosition!=destinationVerticalPosition){
			boolean bHorizontalMoveMade=false;
			boolean bVerticalMoveMade=false;
			if (currentHorizontalPosition!=destinationHorizontalPosition){
				bHorizontalMoveMade=true;
				if (currentHorizontalPosition>destinationHorizontalPosition){
					currentHorizontalPosition--;
				}else{
					currentHorizontalPosition++;
				}
			}
			
			if (currentVerticalPosition!=destinationVerticalPosition){
				bVerticalMoveMade=true;
				if (currentVerticalPosition>destinationVerticalPosition){
					currentVerticalPosition--;
				}else{
					currentVerticalPosition++;
				}
			}
			
			if (bHorizontalMoveMade&&bVerticalMoveMade){
				result+=DIAGONAL_DELAY;
			}else if (bHorizontalMoveMade){
				result+=HORIZONTAL_DELAY;
			}else {
				result+=VERTICAL_DELAY;
			}
			
		}
		
		
		
		
		return result;
	}

}
