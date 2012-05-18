package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.Arrays;


/**
 * IS NEEDED TO STABLISH PROPERTY DOCUMENTS_DIRECTORY WITH FULL PATH TO DOCUMENTS DIRECTORY
 * @author Felix
 *
 */
public class Main {

	private static final String DOCUMENTS_DIRECTORY="DOCUMENTS_DIRECTORY";
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			String sFolder=System.getProperty(DOCUMENTS_DIRECTORY);

			File objFolder=new File(sFolder);
			if (objFolder.isDirectory()){
				File[] objFileArray=objFolder.listFiles();
				Arrays.sort(objFileArray);
				//create Bulk Searcher
				BulkSearcher objSearcher=new BulkSearcher(objFileArray);
				BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
				String numOfTestsString=bf.readLine();
				long numOfTests=Long.parseLong(numOfTestsString);
				long currentNumberOfTest=0;
				while (currentNumberOfTest<numOfTests){
					String sSearchCase=bf.readLine();
					String[] aSearch=sSearchCase.split(" ");
					String sWord=aSearch[0];
					int iNumAppareance=Integer.parseInt(aSearch[1]);
					// register search
					objSearcher.addSearch(sWord, iNumAppareance);
					currentNumberOfTest++;
				}
				// do search
				objSearcher.processSearch();
				//iterate results
				SearchCase[] aSearchCases=objSearcher.getSearchCases();
				for (SearchCase objSearchCase : aSearchCases) {
					System.out.println(String.format("%d-%d-%d",objSearchCase.getFileNumber(),objSearchCase.getLineNumber(),objSearchCase.getWordNumber()));
				}
			}else{
				System.err.println(String.format("%s is not a directory", sFolder));
			}
			
			
		} catch (Exception e) {
			e.printStackTrace();
		}


	}

}
