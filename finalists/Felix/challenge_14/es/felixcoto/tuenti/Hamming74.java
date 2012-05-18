package es.felixcoto.tuenti;


public class Hamming74 {
	private static int[][] BITS_PARITY=new int[][]{new int[]{0,2,4,6},new int[]{1,2,5,6},new int[]{3,4,5,6}};
	private static int[] DATA_BITS=new int[]{2,4,5,6};
	public static boolean[] decodeData(boolean[] aCurrentBlock){
		if (aCurrentBlock.length!=7){
			throw new IllegalArgumentException("Size of block has to be exactly 7 bits");
		}
		boolean[] testParityError=new boolean[BITS_PARITY.length];
		boolean bParityError=false;
		
		// check parity bits
		for (int i=0;i<BITS_PARITY.length;i++){
			int iParity=0;
			for (int iBitToCheck : BITS_PARITY[i]) {
				if (aCurrentBlock[iBitToCheck]){
					iParity++;
				}
			}
			boolean bParityErrorBit=(iParity&0x01)!=0;
			testParityError[i]= bParityErrorBit;
			bParityError|=bParityErrorBit;
			
		}
		boolean[] correctInputBlock;
		if (!bParityError){
			correctInputBlock=aCurrentBlock;
		}else{
			// correct bit error
			int iBitToChange=0;
			for (int i=0;i<testParityError.length;i++){
				if (testParityError[i]){
					iBitToChange+=0x1<<i;
				}
			}
			correctInputBlock=new boolean[aCurrentBlock.length];
			System.arraycopy(aCurrentBlock, 0, correctInputBlock, 0, aCurrentBlock.length);
			iBitToChange--;
			correctInputBlock[iBitToChange]=!correctInputBlock[iBitToChange];
		}
		// extract data
		boolean[] dataResult=new boolean[DATA_BITS.length];
		for (int i=0;i<DATA_BITS.length;i++){
			dataResult[i]=correctInputBlock[DATA_BITS[i]];
		}
		return dataResult;
	}
}
