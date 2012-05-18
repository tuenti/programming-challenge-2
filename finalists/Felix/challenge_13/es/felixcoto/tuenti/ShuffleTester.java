package es.felixcoto.tuenti;

import java.math.BigInteger;
import java.util.HashSet;
import java.util.Set;

class ShuffleTester{
	private final int iNumCards;
	private final int iCutSize;
	/**
	 * @param objNumCards
	 * @param objSizeCut
	 */
	public ShuffleTester(int iNumCards, int iCutSize) {
		this.iNumCards = iNumCards;
		this.iCutSize = iCutSize;
	}
	
	public BigInteger computeShufflesNeeded(){
		ShuffleHelper[] aShuffleHelper=new ShuffleHelper[iNumCards];
		// prepare deck
		for (int i=0;i<aShuffleHelper.length;i++){
			aShuffleHelper[i]=new ShuffleHelper();
		}
		int iNumCardShuffled=0;
		int iPointer1=iCutSize-1;
		int iPointer2=iNumCards-1;
		// do 1 shuffle
		while(iNumCardShuffled<iNumCards){
			if (iPointer1>=0){
				aShuffleHelper[iPointer1].setPositionAfterShuffle(iNumCardShuffled);
				iNumCardShuffled++;
				iPointer1--;
			}
			if (iPointer2>=iCutSize){
				aShuffleHelper[iPointer2].setPositionAfterShuffle(iNumCardShuffled);
				iNumCardShuffled++;
				iPointer2--;
			}
		}
		
		Set<BigInteger> objCyclesDetected=new HashSet<BigInteger>();
		// using the shuffle calculate the times that need every card to return to his start position
		// every position are checked only 1 time
		for (int i=0;i<aShuffleHelper.length;i++){
			if (!aShuffleHelper[i].isCycleChecked()){
				aShuffleHelper[i].setCycleChecked(true);
				int iCurrentPosition=aShuffleHelper[i].getPositionAfterShuffle();
				int iNumShufflesNeeded=1;
				
				while (iCurrentPosition!=i){
					aShuffleHelper[iCurrentPosition].setCycleChecked(true);
					iCurrentPosition=aShuffleHelper[iCurrentPosition].getPositionAfterShuffle();
					iNumShufflesNeeded++;
				}
				objCyclesDetected.add(BigInteger.valueOf(iNumShufflesNeeded));
			}
		}
		
		
		// The result is the least common multiple of all cycle sizes
		BigInteger objCurrentResult=null;
		for (BigInteger objCurrentCycle : objCyclesDetected) {
			if (objCurrentResult==null){
				objCurrentResult=objCurrentCycle;
			}else{
				
				// calculate the least common multiple of cycle and current result
				// the formula used is lcm(a,b)=a*b/gcd(a,b)
				BigInteger objGCD=objCurrentResult.gcd(objCurrentCycle);
				objCurrentResult=objCurrentResult.multiply(objCurrentCycle);
				if (!objGCD.equals(BigInteger.ONE)){
					objCurrentResult=objCurrentResult.divide(objGCD);
				}
				
			}
		}
		
		return objCurrentResult;
	}
	
}

class ShuffleHelper{
	int iPositionAfterShuffle=-1;
	boolean bCycleChecked=false;
	
	
	public int getPositionAfterShuffle() {
		return iPositionAfterShuffle;
	}
	public void setPositionAfterShuffle(int objPositionAfterShuffle) {
		iPositionAfterShuffle = objPositionAfterShuffle;
	}
	public boolean isCycleChecked() {
		return bCycleChecked;
	}
	public void setCycleChecked(boolean objBCycleChecked) {
		bCycleChecked = objBCycleChecked;
	}
	@Override
	public String toString() {
		return String.format("ShuffleHelper [iPositionAfterShuffle=%s, bCycleChecked=%s]", iPositionAfterShuffle, bCycleChecked);
	}
	
	
	
}