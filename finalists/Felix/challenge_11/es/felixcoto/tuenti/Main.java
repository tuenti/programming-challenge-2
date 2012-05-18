package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			InputStream in=Thread.currentThread().getContextClassLoader().getResourceAsStream("descrambler_wordlist.txt");
			ScrabbleDictionary objScrabbleDictionary=new ScrabbleDictionary(in);
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String numOfTestsString=bf.readLine();
			long numOfTests=Long.parseLong(numOfTestsString);
			long currentNumberOfTest=0;
			while (currentNumberOfTest<numOfTests){
				String sCase=bf.readLine();
				String[] sSplitCase=sCase.split(" ");
				ScrabbleDictionary.Entry objResult=objScrabbleDictionary.findBestWord(sSplitCase[0], sSplitCase[1]);
				System.out.println(String.format("%s %d", objResult.getWord(),objResult.getScore()));
				currentNumberOfTest++;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}


	}

}
