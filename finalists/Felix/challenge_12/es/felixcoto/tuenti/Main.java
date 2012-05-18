package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	private static final String[] KEYS=new String[]{
		"62cd275989e78ee56a81f0265a87562e", //power-	Stenography using LSB http://www.irongeek.com/i.php?page=security/unicode-and-lsb-stego-code
		"a541714a17804ac281e6ddda5b707952", //wisdom-	Comment in png file
		"ed8ce15da9b7b5e2ee70634cc235e363"  //courage-	QR-code
	};
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String sChallenge=bf.readLine();
			int[][] iKeys=new int[KEYS.length+1][];
			for (int i=0;i<KEYS.length;i++){
				iKeys[i]=convertHexString(KEYS[i]);
			}
			iKeys[iKeys.length-1]=convertHexString(sChallenge);
			int[] iResponse=new int[sChallenge.length()];
			for (int i=0;i<iResponse.length;i++){
				
				for (int j=0;j<iKeys.length;j++){
					iResponse[i]+=iKeys[j][i];
				}
				iResponse[i]=iResponse[i]%16;
			}
			String sResult=convertToHexString(iResponse);
			System.out.println(sResult);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
	
	private static int[] convertHexString(String s){
		int [] aResult=new int[s.length()];
		for (int i=0;i<s.length();i++){
			aResult[i]=Integer.parseInt(s.substring(i, i+1), 16);
		}
		return aResult;
	}
	
	private static String convertToHexString(int [] iArray){
		StringBuilder sb=new StringBuilder();
		for (int i:iArray){
			sb.append(Integer.toHexString(i));
		}
		return sb.toString();
		
	}

}
