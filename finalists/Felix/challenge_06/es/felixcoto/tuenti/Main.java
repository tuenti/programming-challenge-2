package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

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
				String sTestConfig=bf.readLine();
				String sMessage=bf.readLine();
				Scanner sc=new Scanner(sTestConfig);
				int iWidth=sc.nextInt();
				int iHeight=sc.nextInt();
				int iCount=sc.nextInt();
				CrossStitchResult objResult=computeCrossStitch(sMessage, iWidth, iHeight, iCount);
				int iThread=objResult.getThreadNeeded();
				System.out.println(String.format("Case #%d: %d", currentNumberOfTest+1,iThread));
				currentNumberOfTest++;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		

		
		
	}
	
	
	public static CrossStitchResult computeCrossStitch(String sMessage,int iWidth,int iHeight,int iCount){
		String[] sWords=sMessage.split(" ");
		int iLineSize=0;
		for (String sWord : sWords) {
			if (iLineSize<sWord.length()){
				iLineSize=sWord.length();
			}
		}
		// Initialize font size to fit the largest word
		int iCurrentFontSize=calculateFontSize(iWidth,iCount,iLineSize);
		MessageDisposition objMessageDisposition=computeLines(sWords, iLineSize);
		
		
		// Iterate until message fit
		boolean bFit=false;
		while (!bFit &&iCurrentFontSize>0){
			int iHeightNeeded=calculateDimension(iCurrentFontSize, iCount, objMessageDisposition.getHeight());
			if (iHeightNeeded<=iHeight){
				bFit=true;
			}else{
				// Test if the line size in characters is different
				int iNewLineSize=calculateSizeInCharacters(iWidth, iCount, iCurrentFontSize);
				if (iNewLineSize!=iLineSize){
					// Calculate new message disposition
					objMessageDisposition=computeLines(sWords, iNewLineSize);
					iLineSize=iNewLineSize;
				}else{
					// Simply reduce font size
					iCurrentFontSize--;
				}
			}
		}
		
		// If message fitted
		if (bFit){
			// Adjust font size with final disposition of text 
			iCurrentFontSize=Math.min(calculateFontSize(iWidth, iCount, objMessageDisposition.getWidth()), 
					calculateFontSize(iHeight, iCount, objMessageDisposition.getHeight()));
		}
		// build result
		CrossStitchResult objResult=new CrossStitchResult(bFit,objMessageDisposition.getLines(),iCurrentFontSize,iCount);
		return objResult;
	}
	
	
	 
	
	
	
	private static int calculateFontSize(int iDimension, int iCount, int iSizeInCharacters) {
		
		return (iDimension*iCount)/iSizeInCharacters;
	}

	private static int calculateDimension(double iFontSize,double iCount, double iSizeInCharacters){
		double dResult=(iSizeInCharacters*iFontSize)/iCount;
		dResult=Math.ceil(dResult);
		return (int) dResult;
	}
	
	private static int calculateSizeInCharacters(double dDimension,double dCount, double dFontSize){
		double dResult=(dDimension*dCount)/dFontSize;
		dResult=Math.floor(dResult);
		return (int) dResult;
	}

	private static MessageDisposition computeLines(String[] sWords, int iLineSize) throws IllegalArgumentException{
		List<String> sLines=new ArrayList<String>(sWords.length);
		StringBuilder sbCurrentLine=new StringBuilder(iLineSize);
		// Iterate for every word
		for (String sWord : sWords) {
			// if word is larger than line size throw exception
			if (sWord.length()>iLineSize){
				throw new IllegalArgumentException(sWord+" is larger than line size "+iLineSize);
			}
			// current word fit in current line
			if (sbCurrentLine.length()+sWord.length()<=iLineSize){
				sbCurrentLine.append(sWord);
				sbCurrentLine.append(" ");
			}else{
				// change line
				if (sbCurrentLine.charAt(sbCurrentLine.length()-1)==' '){
					sbCurrentLine.deleteCharAt(sbCurrentLine.length()-1);
				}
				sLines.add(sbCurrentLine.toString());
				sbCurrentLine=new StringBuilder();
				sbCurrentLine.append(sWord);
				sbCurrentLine.append(" ");
			}
		}
		// get last line
		if (sbCurrentLine.charAt(sbCurrentLine.length()-1)==' '){
			sbCurrentLine.deleteCharAt(sbCurrentLine.length()-1);
		}
		sLines.add(sbCurrentLine.toString());

		String[] aResult=new String[sLines.size()];
		aResult=sLines.toArray(aResult);
		return new MessageDisposition(aResult);
		
	}
	

}

class CrossStitchResult{
	private String[] lines;
	private int iFontSize;
	private int iCount;
	private int iThreadNeeded;
	private boolean bFitPossible;
	/**
	 * @param bFitPossible
	 * @param aLines
	 * @param iFontSize
	 * @param iCount
	 */
	public CrossStitchResult(boolean bFitPossible, String[] aLines, int iFontSize, int iCount) {
		this.bFitPossible = bFitPossible;
		this.lines = aLines;
		this.iFontSize = iFontSize;
		this.iCount = iCount;
		this.iThreadNeeded=-1;
	}
	public String[] getLines() {
		return lines;
	}
	public int getFontSize() {
		return iFontSize;
	}
	public int getCount() {
		return iCount;
	}
	public int getThreadNeeded() {
		if (iThreadNeeded==-1){
			if (!bFitPossible){
				iThreadNeeded=0;
			}else{
				int iNumCharacters=0;
				for (String sLine : lines) {
					for (int i=0;i<sLine.length();i++){
						if (sLine.charAt(i)!=' '){
							iNumCharacters++;
						}
					}
				}
				double stimatedStiches=iFontSize*iFontSize;
				stimatedStiches=stimatedStiches/2d;
				stimatedStiches=stimatedStiches*iNumCharacters;
				double stimatedThread=1d/iCount;
				stimatedThread=stimatedThread*stimatedStiches;
				stimatedThread=Math.ceil(stimatedThread);
				iThreadNeeded=(int) stimatedThread;
			}
		}
		return iThreadNeeded;
	}
	public boolean isbFitPossible() {
		return bFitPossible;
	}
	
	
	
	
}


class MessageDisposition{
	private String aLines[];
	private int iWidth;
	
	
	/**
	 * @param objSLines
	 */
	public MessageDisposition(String[] aLines) {
		this.aLines = aLines;
		iWidth=0;
		for (String sLine : aLines) {
			if (sLine.length()>iWidth){
				iWidth=sLine.length();
			}
		}
	}
	public String[] getLines() {
		return aLines;
	}
	public int getWidth() {
		return iWidth;
	}
	
	public int getHeight(){
		return aLines.length;
	}
}