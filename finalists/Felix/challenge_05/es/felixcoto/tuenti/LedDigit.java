package es.felixcoto.tuenti;

import java.util.HashMap;
import java.util.Map;

/**
 * The leds are ordered first outside leds, those that uses on 0, ordered first the upper led and order clockwise, last led is the center led
 * @author Felix
 *
 */
public enum LedDigit {
	DIGIT_0(0,new boolean[]{true,true,true,true,true,true,false}),
	DIGIT_1(1,new boolean[]{false,false,false,false,true,true,false}),
	DIGIT_2(2,new boolean[]{true,true,false,true,true,false,true}),
	DIGIT_3(3,new boolean[]{true,true,true,true,false,false,true}),
	DIGIT_4(4,new boolean[]{false,true,true,false,false,true,true}),
	DIGIT_5(5,new boolean[]{true,false,true,true,false,true,true}),
	DIGIT_6(6,new boolean[]{true,false,true,true,true,true,true}),
	DIGIT_7(7,new boolean[]{true,true,true,false,false,false,false}),
	DIGIT_8(8,new boolean[]{true,true,true,true,true,true,true}),
	DIGIT_9(9,new boolean[]{true,true,true,true,false,true,true});
	 
	private final boolean[] aLeds; 	
	private final int iDigit;
	private int iLedsOn=-1;
	
	
	/**
	 * @param objLed1On
	 * @param objLed2On
	 * @param objLed3On
	 * @param objLed4On
	 * @param objLed5On
	 * @param objLed6On
	 * @param objLed7On
	 */
	private LedDigit(int iDigit, boolean[] aLeds) {
		this.aLeds=aLeds;
		this.iDigit=iDigit;
	}
	
	
	
	private static Map<Integer,LedDigit> lookupMap=new HashMap<Integer, LedDigit>();
	static{
		
		for (LedDigit objCurrentDigit : LedDigit.values()) {
			lookupMap.put(objCurrentDigit.getDigit(), objCurrentDigit);
		}
		
		
	}
	
	public static LedDigit lookup(int iDigit){
		return lookupMap.get(iDigit);
	}
	
	public boolean[] getLeds() {
		return aLeds;
	}
	public int getDigit() {
		return iDigit;
	}
	
	public int getLedsOn(){
		if (iLedsOn==-1){
			iLedsOn=0;
			for (boolean bLedOn : aLeds) {
				if (bLedOn){
					iLedsOn++;
				}
			}
		}
		return iLedsOn;
	}
	
	public int getDeltaLedsOnSwitchFrom(LedDigit otherLedDigit){
		boolean [] otherLeds=otherLedDigit.getLeds();
		int iResult=0;
		for (int i=0;i<aLeds.length;i++){
			if (aLeds[i]&&!otherLeds[i]){
				iResult++;
			}
		}
		return iResult;
	}
	
}
