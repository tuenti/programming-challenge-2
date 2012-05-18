package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String numOfTestsString=bf.readLine();
			long numOfTests=Long.parseLong(numOfTestsString.trim());
			long currentNumberOfTest=0;
			while (currentNumberOfTest<numOfTests){
				String sCase=bf.readLine();
				Scanner sc=new Scanner(sCase);
				int iNumCards=sc.nextInt();
				int iCutSize=sc.nextInt();
				ShuffleTester objTester=new ShuffleTester(iNumCards, iCutSize);
				BigInteger objResult=objTester.computeShufflesNeeded();
				System.out.println(String.format("Case #%d: %s", currentNumberOfTest+1,objResult.toString()));
				currentNumberOfTest++;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} 
	}

}
