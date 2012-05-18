package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.List;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try{
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			PasswordSolver objSolver=new PasswordSolver();
			String sLinea=bf.readLine();
			while(sLinea!=null){
				objSolver.processLetterOrder(sLinea.charAt(0), sLinea.charAt(1));
				objSolver.processLetterOrder(sLinea.charAt(1), sLinea.charAt(2));
				sLinea=bf.readLine();
			}
			List<String> objPasswords=objSolver.getPosiblePasswords();
			// Order password by alphabetic order
			if (objPasswords.size()>1){
				Collections.sort(objPasswords);
			}
			for (String objPassword : objPasswords) {
				System.out.println(objPassword);
			}
		}catch(Exception e){
			e.printStackTrace();
		}
	}

}
