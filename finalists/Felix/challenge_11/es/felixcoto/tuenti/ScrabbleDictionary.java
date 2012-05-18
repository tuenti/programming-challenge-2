package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.NavigableMap;
import java.util.NavigableSet;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.TreeSet;

public class ScrabbleDictionary {
	private static Map<Character, Integer> SCORE_LETTER=new HashMap<Character, Integer>();
	static{
		//1 point: A E I L N O R S T U
		SCORE_LETTER.put('A', 1);
		SCORE_LETTER.put('E', 1);
		SCORE_LETTER.put('I', 1);
		SCORE_LETTER.put('L', 1);
		SCORE_LETTER.put('N', 1);
		SCORE_LETTER.put('O', 1);
		SCORE_LETTER.put('R', 1);
		SCORE_LETTER.put('S', 1);
		SCORE_LETTER.put('T', 1);
		SCORE_LETTER.put('U', 1);
		
		//2 points: D G
		SCORE_LETTER.put('D', 2);
		SCORE_LETTER.put('G', 2);
		
		//3 points: B C M P
		SCORE_LETTER.put('B', 3);
		SCORE_LETTER.put('C', 3);
		SCORE_LETTER.put('M', 3);
		SCORE_LETTER.put('P', 3);
		
		//4 points: F H V W Y
		SCORE_LETTER.put('F', 4);
		SCORE_LETTER.put('H', 4);
		SCORE_LETTER.put('V', 4);
		SCORE_LETTER.put('W', 4);
		SCORE_LETTER.put('Y', 4);
		
		//5 points: K
		SCORE_LETTER.put('K', 5);
		
		//8 points: J X
		SCORE_LETTER.put('J', 8);
		SCORE_LETTER.put('X', 8);
		
		//10 points: Q Z
		SCORE_LETTER.put('Q', 10);
		SCORE_LETTER.put('Z', 10);
	}
	
	private Map<Character, NavigableMap<Integer, NavigableSet<Entry>>> objDictionary;
	
	

	public ScrabbleDictionary(InputStream objDictionaryStream) throws IOException{
		objDictionary=new HashMap<Character, NavigableMap<Integer,NavigableSet<Entry>>>();
		BufferedReader bf=new BufferedReader(new InputStreamReader(objDictionaryStream));
		String sWord=bf.readLine();
		while (sWord!=null){
			storeWord(sWord);
			sWord=bf.readLine();
		}
		
	}
	
	
	
	private void storeWord(String sWord) {
		Entry objEntry=new Entry(sWord);
		// iterate for individual letters, removing duplicates
		for (Map.Entry<Character, Integer> objEntryMap : objEntry.getLetterOcurrence().entrySet()) {
		
			Character objCurrentCharacter=objEntryMap.getKey();
			NavigableMap<Integer, NavigableSet<Entry>> objMapForCharacter=null;
			// recover or create map for current character
			if (objDictionary.containsKey(objEntryMap.getKey())){
				objMapForCharacter=objDictionary.get(objCurrentCharacter);
			}else{
				objMapForCharacter=new TreeMap<Integer, NavigableSet<Entry>>();
				objDictionary.put(objCurrentCharacter, objMapForCharacter);
			}
			NavigableSet<ScrabbleDictionary.Entry> objSetForOccurrence;
			Integer iOccurrence=objEntryMap.getValue();
			//recover or create map for current num of occurrences of letter
			if (objMapForCharacter.containsKey(iOccurrence)){
				objSetForOccurrence=objMapForCharacter.get(iOccurrence);
			}else{
				objSetForOccurrence=new TreeSet<ScrabbleDictionary.Entry>();
				objMapForCharacter.put(iOccurrence, objSetForOccurrence);
			}
			//store in navigablemap
			objSetForOccurrence.add(objEntry);
		}
		
		
	}
	
	
	public ScrabbleDictionary.Entry findBestWord(String sRack,String sBoardWord){
		// initialize usable letters in a more usable format
		Map<Character,Integer> objRackConfig=new HashMap<Character, Integer>();
		for (int i=0;i<sRack.length();i++){
			char character=sRack.charAt(i);
			int iOcurrence=1;
			if (objRackConfig.containsKey(character)){
				iOcurrence=objRackConfig.get(character)+1;
			}
			objRackConfig.put(character,iOcurrence);
		}
		// remove duplicate letters of word
		Set<Character> objBoardWord=new HashSet<Character>();
		for (int i=0;i<sBoardWord.length();i++){
			objBoardWord.add(sBoardWord.charAt(i));
		}
		Entry objResult=null;
		
		// iterate over letters in board
		for (Character objCharacter : objBoardWord) {
			NavigableMap<Character,Integer> objCharacterPosibilities=new TreeMap<Character, Integer>(objRackConfig);
			// complete usable characters
			if (objCharacterPosibilities.containsKey(objCharacter)){
				int iOcurrence=objCharacterPosibilities.get(objCharacter)+1;
				objCharacterPosibilities.put(objCharacter, iOcurrence);
			}else{
				objCharacterPosibilities.put(objCharacter,1);
			}
			// With this fake entry limit the search to the best word, score and lexical order, if we use all available letters
			FakeEntry objFakeEntry=new FakeEntry(objCharacterPosibilities);
			NavigableMap<Integer, NavigableSet<Entry>> objMapForCharacter=objDictionary.get(objCharacter);
			
			if (objMapForCharacter!=null&&
					(objResult==null||
					objFakeEntry.compareTo(objResult)<0)){
				Integer iOcurrence=objCharacterPosibilities.get(objCharacter);
				NavigableMap<Integer, NavigableSet<Entry>> objMapForCharacterLimited=objMapForCharacter.headMap(iOcurrence, true);
				// Iterate for Navigable set that contains words with letter in board
				for (NavigableSet<Entry> objCandidateEntrySet : objMapForCharacterLimited.values()) {
					NavigableSet<Entry> objCandidateEntrySetLimited=objCandidateEntrySet;
					
					//Limit search 
					objCandidateEntrySetLimited=objCandidateEntrySetLimited.tailSet(objFakeEntry,true);
					if (objResult!=null){
						objCandidateEntrySetLimited=objCandidateEntrySetLimited.headSet(objResult, false);
					}
					
					boolean bCandidateFinded=false;
					Iterator<Entry> itEntry=objCandidateEntrySetLimited.iterator();
					// If we find a correct value, end this search because all next posibilities are worse
					while (itEntry.hasNext()&&!bCandidateFinded){
						Entry objCandidateEntry=itEntry.next();
						Map<Character, Integer> objLetterOcurrence=objCandidateEntry.getLetterOcurrence();
						Iterator<Map.Entry<Character, Integer>> itLetterOcurrence=objLetterOcurrence.entrySet().iterator();
						boolean bCandidateFit=true;
						//check letters of word
						while (itLetterOcurrence.hasNext()&&bCandidateFit){
							Map.Entry<Character, Integer> objCurrentLetterOcurrence=itLetterOcurrence.next();
							if (objCharacterPosibilities.containsKey(objCurrentLetterOcurrence.getKey())){
								if (objCurrentLetterOcurrence.getValue()>objCharacterPosibilities.get(objCurrentLetterOcurrence.getKey())){
									bCandidateFit=false;
								}
							}else{
								bCandidateFit=false;
							}
						}
						// if a candidate fit, store as best result
						if (bCandidateFit){
							objResult=objCandidateEntry;
							bCandidateFinded=true;
						}
					}
				}
			}
			

		}
		return objResult;
	}

	
	private class FakeEntry extends Entry{

		public FakeEntry(SortedMap<Character,Integer> objLetterOcurrence) {
			super("AAA");
			int iFakeScore=0;
			StringBuilder sb=new StringBuilder();
			for (Map.Entry<Character, Integer> objLetterEntry : objLetterOcurrence.entrySet()) {
				iFakeScore+=objLetterEntry.getValue()*SCORE_LETTER.get(objLetterEntry.getKey());
				for (int i=0;i<objLetterEntry.getValue();i++){
					sb.append(objLetterEntry.getKey());
				}
			}
			iScore=iFakeScore;
			sWord=sb.toString();
		}
		
	}
	
	
	class Entry implements Comparable<Entry>{
		String sWord;
		int iScore;
		Map<Character, Integer> objLetterOcurrence;
		/**
		 * @param objSWord
		 */
		public Entry(String word) {
			this.sWord = word;
			iScore=0;
			objLetterOcurrence=new HashMap<Character, Integer>();
			for (int i=0;i<sWord.length();i++){
				char currentCharacter=sWord.charAt(i);
				iScore+=SCORE_LETTER.get(currentCharacter);
				int iResult=1;
				if (objLetterOcurrence.containsKey(currentCharacter)){
					iResult=objLetterOcurrence.get(currentCharacter)+1;
				}
				objLetterOcurrence.put(currentCharacter, iResult);
			}
			objLetterOcurrence=Collections.unmodifiableMap(objLetterOcurrence);
		}
		public String getWord() {
			return sWord;
		}
		public int getScore() {
			return iScore;
		}
		public Map<Character, Integer> getLetterOcurrence() {
			return objLetterOcurrence;
		}
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + getOuterType().hashCode();
			result = prime * result + iScore;
			result = prime * result + ((sWord == null) ? 0 : sWord.hashCode());
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
			Entry other = (Entry) obj;
			if (!getOuterType().equals(other.getOuterType()))
				return false;
			if (iScore != other.iScore)
				return false;
			if (sWord == null) {
				if (other.sWord != null)
					return false;
			} else if (!sWord.equals(other.sWord))
				return false;
			return true;
		}
		private ScrabbleDictionary getOuterType() {
			return ScrabbleDictionary.this;
		}
		@Override
		public int compareTo(Entry objOtherEntry) {
			int iResult;
			if (this.iScore>objOtherEntry.getScore()){
				iResult= -1;
			}else if (this.iScore<objOtherEntry.getScore()){
				iResult=1;
			}else{
				iResult=this.sWord.compareTo(objOtherEntry.getWord());
			}
			return iResult;
		}
		@Override
		public String toString() {
			return String.format("Entry [sWord=%s, iScore=%s]", sWord, iScore);
		}
		
		
	}
	
	public static void main(String[] args) {
		try {
			long lInicio=System.currentTimeMillis();
			InputStream in=Thread.currentThread().getContextClassLoader().getResourceAsStream("descrambler_wordlist.txt");
			ScrabbleDictionary objScrabbleDictionary=new ScrabbleDictionary(in);
			long lFin=System.currentTimeMillis();
			System.out.println(lFin-lInicio);
			
			lInicio=System.currentTimeMillis();
			ScrabbleDictionary.Entry objEntry=objScrabbleDictionary.findBestWord("MN", "HELL");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("SWAMEO", "TUENTI");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("GDC", "POA");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			
			 
			 
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("DL", "ARENIG");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			
			
			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("DUJ", "CELLULOTOXIC");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			
			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("IGG", "UNHUMOURED");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("RD", "COLTHOOD");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("MM", "GREENCOAT");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("CMH", "PANNERY");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("RH", "HUNTSWOMAN");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("LXYTA", "INTERLEAVER");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);

			 
			
			lInicio=System.currentTimeMillis();
			objEntry=objScrabbleDictionary.findBestWord("MOCMH", "FACULTATIVELY");
			lFin=System.currentTimeMillis();
			System.out.println(objEntry.toString());
			System.out.println(lFin-lInicio);



		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	
}
