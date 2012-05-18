package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.NavigableMap;
import java.util.TreeMap;

public class Main {

	private static boolean longInitialized=false;
	private static boolean bigIntegerInitialized=false;
	
	private static long[] firstNumbersLong;
	private static NavigableMap<Long,Integer> bitsForNumberLong;
	private static BigInteger[] firstNumbersBig;
	private static NavigableMap<BigInteger,Integer> bitsForNumberBig;
	
	
	
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
				int iResult=0;
				
				try {
					long lCurrentTest=Long.parseLong(currentInputTest);
					iResult=numberOfOnesLong(lCurrentTest);
				} catch (NumberFormatException e) {
					BigInteger bigNumber=new BigInteger(currentInputTest);
					iResult=numberOfOnesBig(bigNumber);
				}
				

				System.out.println("Case #"+(currentNumberOfTest+1)+": "+iResult);
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

	private static void initializeLong(){
		firstNumbersLong=new long[64];
		bitsForNumberLong=new TreeMap<Long, Integer>();
		bitsForNumberLong.put(new Long(0), 0);
		long currentNumber=1;
		for (int i=1;i<firstNumbersLong.length;i++){
			firstNumbersLong[i]=currentNumber;
			bitsForNumberLong.put(currentNumber, i);
			currentNumber=currentNumber<<1;
			currentNumber=currentNumber|1;
		}
	}
	
	private static void initializeBig(){
		firstNumbersBig=new BigInteger[65];
		firstNumbersBig[0]=BigInteger.ZERO;
		bitsForNumberBig=new TreeMap<BigInteger, Integer>();
		bitsForNumberBig.put(BigInteger.ZERO, 0);
		for (int i=1;i<firstNumbersBig.length;i++){
			BigInteger objNewInteger=firstNumbersBig[i-1].shiftLeft(1);
			objNewInteger=objNewInteger.setBit(0);
			firstNumbersBig[i]=objNewInteger;
			bitsForNumberBig.put(objNewInteger, i);
		}
	}
	
	private static int numberOfOnesLong(long lNumber){
		if (!longInitialized){
			initializeLong();
			longInitialized=true;
		}
		long lFloorNumber=bitsForNumberLong.floorKey(lNumber);
		int iResult=bitsForNumberLong.get(lFloorNumber);
		long lSecondNumber=lNumber-lFloorNumber;
		if (lSecondNumber>0){
			long lCeilForSecondNumber=bitsForNumberLong.ceilingKey(lSecondNumber);
			int iBitsForSecond=bitsForNumberLong.get(lCeilForSecondNumber);
			long lCurrentMask=1;
			for (int i=0;i<iBitsForSecond;i++){
				if ((lSecondNumber&lCurrentMask)>0){
					iResult++;
				}
				lCurrentMask=lCurrentMask<<1;
			}
		}
		return iResult;
	}
	
	private static int numberOfOnesBig(BigInteger bigNumber){
		if (!bigIntegerInitialized){
			initializeBig();
			bigIntegerInitialized=true;
		}
		
		BigInteger floorNumber=bitsForNumberBig.floorKey(bigNumber);
		int iResult=bitsForNumberBig.get(floorNumber);
		BigInteger secondNumber=bigNumber.subtract(floorNumber);
		while (!secondNumber.equals(BigInteger.ZERO)){
			iResult++;
			int iLowestBitSet=secondNumber.getLowestSetBit();
			secondNumber=secondNumber.shiftRight(iLowestBitSet+1);
		}
		return iResult;
		
	}
}
