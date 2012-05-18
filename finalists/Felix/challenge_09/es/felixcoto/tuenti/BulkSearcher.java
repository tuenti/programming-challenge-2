package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BulkSearcher {
	private int iNumberOfCasesPending=0;
	private Map<String,List<SearchCase>> objPendingSearches;
	private List<SearchCase> objAllSearchCases;
	File[] aFiles;
	

	public BulkSearcher(File[] aFiles){
		this.aFiles=aFiles;
		objPendingSearches=new HashMap<String, List<SearchCase>>();
		objAllSearchCases=new LinkedList<SearchCase>();
	}
	
	public void addSearch(String sWord,int iNumAppareance){
		iNumberOfCasesPending++;
		SearchCase objNewSearchCase=new SearchCase(sWord, iNumAppareance);
		objAllSearchCases.add(objNewSearchCase);
		String sWordLowCase=sWord.toLowerCase();
		if (objPendingSearches.containsKey(sWordLowCase)){
			objPendingSearches.get(sWordLowCase).add(objNewSearchCase);
		}else{
			List<SearchCase> objNewList=new LinkedList<SearchCase>();
			objNewList.add(objNewSearchCase);
			objPendingSearches.put(sWordLowCase, objNewList);
		}
	}
	
	public void processSearch() throws Exception{
		Pattern objCurrentPattern=generatePattern();
		int iCurrentWordsInPattern=objPendingSearches.keySet().size();
		int iFileNumber=0;
		// Iterate for every file until all searches done
		while (iFileNumber<aFiles.length&&iNumberOfCasesPending>0){
			BufferedReader bf=new BufferedReader(new FileReader(aFiles[iFileNumber]));
			iFileNumber++;
			String sLine=bf.readLine();
			int iLineNumber=1;
			
			// read all lines of current file while there are searches pending
			while (sLine!=null && iNumberOfCasesPending>0){
				//Update pattern with pending words
				if (objPendingSearches.keySet().size()!=iCurrentWordsInPattern){
					objCurrentPattern=generatePattern();
					iCurrentWordsInPattern=objPendingSearches.keySet().size();
				}
				Matcher objMatcher=objCurrentPattern.matcher(sLine);
				int iCurrentLinePosition=0;
				//test if matcher finds any of the pending words
				while (objMatcher.find(iCurrentLinePosition)&&iNumberOfCasesPending>0){
					// set pointer to the space after the word finded
					iCurrentLinePosition=objMatcher.end(1);
					
					// calculate the word number
					int iCharNum=objMatcher.start(1);
					int iWordNumber=1;
					if (iCharNum>0){
						String sLineBefore=sLine.substring(0,iCharNum);
						String[] sWordsBefore=sLineBefore.split(" ");
						iWordNumber=sWordsBefore.length+1;
					}
					
					// extract the word
					String sWord=objMatcher.group(1);
					sWord=sWord.toLowerCase();
					if (objPendingSearches.containsKey(sWord)){
						List<SearchCase> objCurrentCases=objPendingSearches.get(sWord);
						Iterator<SearchCase> it=objCurrentCases.iterator();
						// Notify to all SearchCase if there are multiple search for same word
						while (it.hasNext()){
							SearchCase objCurrentCase=it.next();
							boolean bFinded=objCurrentCase.registerAppareance(iFileNumber, iLineNumber, iWordNumber);
							if (bFinded){
								iNumberOfCasesPending--;
								it.remove();
							}
						}
						if (objCurrentCases.isEmpty()){
							objPendingSearches.remove(sWord);
						}
					}
				}
				
				sLine=bf.readLine();
				iLineNumber++;
			}
		}
		
	}
	
	
	private Pattern generatePattern(){
		StringBuilder sbWords=new StringBuilder();
		for (String sWord : objPendingSearches.keySet()) {
			sbWords.append(sWord);
			sbWords.append("|");
		}
		sbWords.deleteCharAt(sbWords.length()-1);
		StringBuilder sbPattern=new StringBuilder();
		sbPattern.append("(?:^|\\s)(");
		sbPattern.append(sbWords.toString());
		sbPattern.append(")(?:$|\\s)");
		Pattern objResult=Pattern.compile(sbPattern.toString(), Pattern.CASE_INSENSITIVE);
		return objResult;
	}
	
	public SearchCase[] getSearchCases(){
		SearchCase[] objResult=new SearchCase[objAllSearchCases.size()];
		objResult=objAllSearchCases.toArray(objResult);
		return objResult;
	}
	
}

class SearchCase{
	private String sWord;
	private int iAppareancesPending;
	
	private int iFileNumber;
	private int iLineNumber;
	private int iWordNumber;
	
	/**
	 * @param objSWord
	 * @param objAppareancesPending
	 */
	public SearchCase(String objSWord, int objAppareancesPending) {
		sWord = objSWord;
		iAppareancesPending = objAppareancesPending;
	}
	
	public boolean registerAppareance(int iFileNumber,int iLineNumber, int iWordNumber){
		iAppareancesPending--;
		if (iAppareancesPending==0){
			this.iFileNumber=iFileNumber;
			this.iLineNumber=iLineNumber;
			this.iWordNumber=iWordNumber;
			return true;
		}else{
			if (iAppareancesPending>0){
				return false;
			}else{
				return true;
			}
		}
	}

	public int getFileNumber() {
		return iFileNumber;
	}

	public int getLineNumber() {
		return iLineNumber;
	}

	public int getWordNumber() {
		return iWordNumber;
	}
	
	
}
