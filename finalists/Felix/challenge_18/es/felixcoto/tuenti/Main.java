package es.felixcoto.tuenti;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			Scanner sc=new Scanner(System.in);
			int iNumberOfCases=sc.nextInt();
			int iCasesExecuted=0;
			while (iCasesExecuted<iNumberOfCases){
				iCasesExecuted++;
				long lInput=sc.nextLong();
				
				// The result is obtained using the following formula
				// 1+((n(n+1))/2)
				BigInteger objResult=BigInteger.valueOf(lInput+1);
				objResult=objResult.multiply(BigInteger.valueOf(lInput));
				objResult=objResult.shiftRight(1);// equivalent to divide by 2
				objResult=objResult.add(BigInteger.ONE);
						
				System.out.println(String.format("Case #%s: %s", iCasesExecuted,objResult));
			}
			
			
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		
		

	}

}
