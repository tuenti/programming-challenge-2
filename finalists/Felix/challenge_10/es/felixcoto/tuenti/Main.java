package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Deque;
import java.util.LinkedList;

public class Main {

	public static void main(String[] args) {
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String sLine=bf.readLine();
			while (sLine!=null){
				String[] sSentence=sLine.split(" ");
				Deque<Long> objStack=new LinkedList<Long>();
				for (String sCurrentToken : sSentence) {
					// lookup command
					M00reCommands objM00reCommand=M00reCommands.lookupOperator(sCurrentToken);
					if (objM00reCommand!=null){
						objM00reCommand.execute(objStack);
					}else{
						// if is not a command, treat as Number
						Long lNumber=Long.parseLong(sCurrentToken);
						objStack.push(lNumber);
					}
				}
				sLine=bf.readLine();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

}
