package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class Main {
	

	private static final long MILISECONDS_IN_DAY=1000*60*60*24;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {
			Clock oldClock=new OldClock();
			Clock newClock=new NewClock();
			DateFormat df=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String sLine=bf.readLine();
			while (sLine!=null){
				String sDate1=sLine.substring(0,19);
				String sDate2=sLine.substring(22);
				
				Date objDate1=df.parse(sDate1);
				Date objDate2=df.parse(sDate2);
				long lDifference=calculateDifferenceSwitchOnClocks(objDate1,objDate2,oldClock,newClock);
				System.out.println(lDifference);
				sLine=bf.readLine();
				
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		
		
	
		
	}


	private static long calculateDifferenceSwitchOnClocks(Date objDate1, Date objDate2,Clock oldClock, Clock newClock) {
		long lResult=0;
		Calendar objCalendar1=Calendar.getInstance();
		objCalendar1.setTime(objDate1);
		Calendar objCalendar2=Calendar.getInstance();
		objCalendar2.setTime(objDate2);
		
		int iInitialHour=objCalendar1.get(Calendar.HOUR_OF_DAY);
		int iInitialMinute=objCalendar1.get(Calendar.MINUTE);
		int iInitialSecond=objCalendar1.get(Calendar.SECOND);
		
		int iFinalHour=objCalendar2.get(Calendar.HOUR_OF_DAY);
		int iFinalMinute=objCalendar2.get(Calendar.MINUTE);
		int iFinalSecond=objCalendar2.get(Calendar.SECOND);
		
		long lDifferenceOfDays=(objDate2.getTime()-objDate1.getTime())/MILISECONDS_IN_DAY;
		
		long lSwitchOnOldClock=oldClock.calculateSwitchOnBetweenHour(iInitialHour, iInitialMinute, iInitialSecond, iFinalHour, iFinalMinute, iFinalSecond);
		lSwitchOnOldClock+=oldClock.calculateSwitchOnCompleteDay()*lDifferenceOfDays;
		
		long lSwitchOnNewClock=newClock.calculateSwitchOnBetweenHour(iInitialHour, iInitialMinute, iInitialSecond, iFinalHour, iFinalMinute, iFinalSecond);
		lSwitchOnNewClock+=newClock.calculateSwitchOnCompleteDay()*lDifferenceOfDays;
		
		lResult=lSwitchOnOldClock-lSwitchOnNewClock;
		
		return lResult;
	}

	
		
	
	
	
	
	
}

abstract class  Clock{
	
	long lCompleteDayTransition=-1; 
	
	public abstract long calculateSwitchOnBetweenHour(int initialHour,int initialMinute,int initialSecond,int finalHour,int finalMinute, int finalSecond);

	public long calculateSwitchOnCompleteDay() {
		if (lCompleteDayTransition==-1){
			lCompleteDayTransition=calculateSwitchOnBetweenHour(0,0,0,23,59,59);
			lCompleteDayTransition+=calculateSwitchOnBetweenHour(23,59,59,0,0,0);
		}
		return lCompleteDayTransition;
	}
	
	protected void checkInput(int iInput,int iLowLimit, int iHighLimit) {
		if(iInput>iHighLimit){
			throw new IllegalArgumentException(iInput+">"+iHighLimit);
		}
		if(iInput<iLowLimit){
			throw new IllegalArgumentException(iInput+"<"+iLowLimit);
		}

	}
	
	

	protected long sumIntegersTransitions(int [] intArray, int iOrigin, int iEnd, int iLimit){
		if (iLimit==-1){
			iLimit=intArray.length;
		}
		long lResult=0;
		int i=iOrigin;
		while (i!=iEnd){
			lResult+=intArray[i];
			i++;
			if (i>=intArray.length){
				i=0;
			}
		}
		lResult+=intArray[i];
		return lResult;
		
	}
	
	protected int differenceNumbersLimited(int iInitial,int iFinal, int iLimit){
		int iResult=iFinal-iInitial;
		if (iResult<0){
			iResult=iResult+iLimit;
		}
		return iResult;
	}
	
	
	
	protected int sumNumbersMod(int iFirst,int iSecond, int iLimit){
		int iResult=iSecond+iFirst;
		if (iResult<0||iResult>=iLimit){
			iResult=iResult%iLimit;
			if (iResult<0){
				iResult+=iLimit;
			}
		}
		
		return iResult;
	}
	

	
	
}





class NewClock extends Clock{

	private final int aNumberOfLedsSwitchOn24[]=new int[24];
	private final int aNumberOfLedsSwitchOn60[]=new int[60];

	
	private int iCompleteRotationSwitchOn60;
	
	

	public NewClock(){
		
		int iLastUnits=0;
		int iLastTens=0;
		int iUnits=1;
		int iTens=0;
		for (int i=1;i<60;i++){
			
			
			LedDigit objUnitsDigit=LedDigit.lookup(iUnits);
			LedDigit objLastUnitsDigit=LedDigit.lookup(iLastUnits);
			int iCurrentLedsSwitchOn=objUnitsDigit.getDeltaLedsOnSwitchFrom(objLastUnitsDigit);
			if (iLastTens!=iTens){
				LedDigit objTensDigit=LedDigit.lookup(iTens);
				LedDigit objLastTensDigit=LedDigit.lookup(iLastTens);
				iCurrentLedsSwitchOn+=objTensDigit.getDeltaLedsOnSwitchFrom(objLastTensDigit);
				iLastTens=iTens;
			}
			
			
			
			if (i<24){
				aNumberOfLedsSwitchOn24[i]=iCurrentLedsSwitchOn;
			}
			aNumberOfLedsSwitchOn60[i]=iCurrentLedsSwitchOn;
			
			iLastUnits=iUnits;
			iUnits++;
			if (iUnits>=10){
				iUnits=0;
				iLastTens=iTens;
				iTens++;
			}
		}
		
		//Calculate 0 transition
		aNumberOfLedsSwitchOn24[0]=LedDigit.DIGIT_0.getDeltaLedsOnSwitchFrom(LedDigit.DIGIT_2)+LedDigit.DIGIT_0.getDeltaLedsOnSwitchFrom(LedDigit.DIGIT_3);
		aNumberOfLedsSwitchOn60[0]=LedDigit.DIGIT_0.getDeltaLedsOnSwitchFrom(LedDigit.DIGIT_5)+LedDigit.DIGIT_0.getDeltaLedsOnSwitchFrom(LedDigit.DIGIT_9);
		
		iCompleteRotationSwitchOn60=0;
		for (int i : aNumberOfLedsSwitchOn60) {
			iCompleteRotationSwitchOn60+=i;
		}

	}
	
	
	public long calculateSwitchOnBetweenHour(int iInitialHour, int iInitialMinute, int iInitialSecond, int iFinalHour, int iFinalMinute,
			int iFinalSecond) {
		
		checkInput(iInitialHour,0,23);
		checkInput(iInitialMinute,0,59);
		checkInput(iInitialSecond,0,59);
		checkInput(iFinalHour,0,23);
		checkInput(iFinalMinute,0,59);
		checkInput(iFinalSecond,0,59);
		long lResult=0;
		
		int iCurrentSecond=iInitialSecond;
		int iCurrentMinute=iInitialMinute;
		int iCurrentHour=iInitialHour;
		//Adjust seconds
		if (iCurrentSecond!=iFinalSecond){
			
			lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60, sumNumbersMod(iCurrentSecond, 1, 60), iFinalSecond, -1);
			// if there is a change of minute
			if (iCurrentSecond>iFinalSecond){
				iCurrentMinute++;
				if (iCurrentMinute==60){
					iCurrentMinute=0;
					iCurrentHour++;
					if (iCurrentHour==24){
						iCurrentHour=0;
					}
					lResult+=aNumberOfLedsSwitchOn24[iCurrentHour];
				}
				lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute];
			}
			
			iCurrentSecond=iFinalSecond;
		}
		
		//Adjust Minute
		
		if (iCurrentMinute!=iFinalMinute){
			lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60, sumNumbersMod(iCurrentMinute, 1, 60) , iFinalMinute, -1);
			int iDiferenceMinutes=differenceNumbersLimited(iCurrentMinute,iFinalMinute, 60);
			// Sum seconds complete transitions
			lResult+=iCompleteRotationSwitchOn60*iDiferenceMinutes;
			// if there is a change in hour
			if (iCurrentMinute>iFinalMinute){
				iCurrentHour++;
				if (iCurrentHour==24){
					iCurrentHour=0;
				}
				lResult+=aNumberOfLedsSwitchOn24[iCurrentHour];
			}
			iCurrentMinute=iFinalMinute;
		}
		
		// Adjust Hour
		if (iCurrentHour!=iFinalHour){
			lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn24, sumNumbersMod(iCurrentHour, 1, 24), iFinalHour, 24);
			int iDifferenceHour=differenceNumbersLimited(iCurrentHour, iFinalHour, 24);
			//Sum minute transitions
			lResult+=iCompleteRotationSwitchOn60*iDifferenceHour;
			//Sum second transitions
			lResult+=iCompleteRotationSwitchOn60*iDifferenceHour*60;
		}
		
		return lResult;
	}

	
}



class OldClock extends Clock{

	final int aNumberOfLedsSwitchOn60[]=new int[60];

	
	long lCompleteRotationSwitchOn60;
	
	long lCompleteDayTransition=-1;

	public OldClock(){
		
		int iUnits=0;
		int iTens=0;
		for (int i=0;i<60;i++){
			LedDigit objUnitsDigit=LedDigit.lookup(iUnits);
			LedDigit objTensDigit=LedDigit.lookup(iTens);
			int iCurrentLedsSwitchOn=objUnitsDigit.getLedsOn()+objTensDigit.getLedsOn();
			aNumberOfLedsSwitchOn60[i]=iCurrentLedsSwitchOn;
			
			iUnits++;
			if (iUnits>=10){
				iUnits=0;
				iTens++;
			}
		}
		
		lCompleteRotationSwitchOn60=0;
		for (int i=0;i<aNumberOfLedsSwitchOn60.length;i++){
			int iCurrent=aNumberOfLedsSwitchOn60[i];
			lCompleteRotationSwitchOn60+=iCurrent;
		}
		
		
		

	}
	
	public long calculateSwitchOnBetweenHour(int iInitialHour, int iInitialMinute, int iInitialSecond, int iFinalHour, int iFinalMinute,
			int iFinalSecond) {
		
		checkInput(iInitialHour,0,23);
		checkInput(iInitialMinute,0,59);
		checkInput(iInitialSecond,0,59);
		checkInput(iFinalHour,0,23);
		checkInput(iFinalMinute,0,59);
		checkInput(iFinalSecond,0,59);
		long lResult=0;
		
		int iCurrentSecond=iInitialSecond;
		int iCurrentMinute=iInitialMinute;
		int iCurrentHour=iInitialHour;
		
		// move seconds to 0 if necesary
		if (iCurrentSecond!=0 && 
				(iCurrentSecond>iFinalSecond||
				 iCurrentMinute!=iFinalMinute||
				 iCurrentHour!=iFinalHour)){
			
			
			
			// Sum switch on of minute and hour display until 59 seconds
			int iDifferenceSeconds=differenceNumbersLimited(iCurrentSecond, 59, 60);
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute]*iDifferenceSeconds;
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*iDifferenceSeconds;

			iCurrentSecond=sumNumbersMod(iCurrentSecond, 1, 60);
			if (iCurrentSecond!=0){
				lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60,iCurrentSecond, 59, -1);
			}

			iCurrentSecond=0;
			
			iCurrentMinute++;
			if (iCurrentMinute==60){
				iCurrentMinute=0;
				iCurrentHour++;
				if (iCurrentHour==24){
					iCurrentHour=0;
					
				}
			}
			
			// sum switch on of 0 second transition
			lResult+=aNumberOfLedsSwitchOn60[iCurrentSecond];
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute];
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour];
			
			
		}
		
		
		
		// move minute to 0 if necesary
		
		if (iCurrentMinute!=0 &&
				(iCurrentMinute>iFinalMinute||
						iCurrentHour!=iFinalHour)){
			// sum seconds transitions
			int iDifferenceMinute=differenceNumbersLimited(iCurrentMinute, 0,60);
			lResult+=lCompleteRotationSwitchOn60*iDifferenceMinute;	
			
			
			iDifferenceMinute=differenceNumbersLimited(iCurrentMinute, 59,60);
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute]*59; //the current minute blinks 59 times
			iCurrentMinute=sumNumbersMod(iCurrentMinute, 1, 60);
			if (iCurrentMinute!=0){
				lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60, iCurrentMinute, 59, -1)*60;// each minute transition blinks 60 times
			}
			
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*59;// The current hour blinks 59 times in the current minute
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*iDifferenceMinute*60;// The current hour blinks 60 times in each other minute until 00
			
			iCurrentMinute=0;
			
			iCurrentHour++;
			if (iCurrentHour==24){
				iCurrentHour=0;
			}
			
			// sum switch on of 0 minute transition
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute];
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour];
			
		}
		
		// Adjust Hour
		if (iCurrentHour!=iFinalHour){
			int iDifferenceHour=differenceNumbersLimited(iCurrentHour, iFinalHour, 24);
			//Sum minute transitions
			lResult+=lCompleteRotationSwitchOn60*iDifferenceHour*60;
			//Sum second transitions
			lResult+=lCompleteRotationSwitchOn60*iDifferenceHour*60;
			
			
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*3599; // blink of 0 instant is already counted
			iCurrentHour=sumNumbersMod(iCurrentHour,1,24);
			if (iCurrentHour!=iFinalHour){
				lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60, iCurrentHour , sumNumbersMod(iFinalHour, -1, 24), 24)*3600;// each hour blinks 3600 times in a hour
			}
			lResult+=aNumberOfLedsSwitchOn60[iFinalHour];// sum switch on 0 transition
			iCurrentHour=iFinalHour;
		}
		

		
		// Adjust minute
		if (iCurrentMinute!=iFinalMinute){
			// sum seconds transitions
			int iDifferenceMinute=differenceNumbersLimited(iCurrentMinute, iFinalMinute,60);
			lResult+=lCompleteRotationSwitchOn60*iDifferenceMinute;	
			
			
			iDifferenceMinute=differenceNumbersLimited(iCurrentMinute, sumNumbersMod(iFinalMinute, -1, 60),60);
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute]*59; //the current minute blinks 59 times
			iCurrentMinute=sumNumbersMod(iCurrentMinute, 1, 60);
			if (iCurrentMinute!=iFinalMinute){
				lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60, iCurrentMinute, sumNumbersMod(iFinalMinute, -1, 60), -1)*60;// each minute transition blinks 60 times
			}
			
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*59;// The current hour blinks 59 times in the current minute
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*iDifferenceMinute*60;// The current hour blinks 60 times in each other minute until 00
			
			iCurrentMinute=iFinalMinute;
			
			
			// sum switch on final minute transition
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute];
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour];
			
			
		}
		
		
		//Adjust second
		if (iCurrentSecond!=iFinalSecond){
			int iDifferenceSeconds=differenceNumbersLimited(iCurrentSecond, sumNumbersMod(iFinalSecond, -1, 60), 60);
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute]*iDifferenceSeconds;
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour]*iDifferenceSeconds;

			iCurrentSecond=sumNumbersMod(iCurrentSecond, 1, 60);
			if (iCurrentSecond!=iFinalSecond){
				lResult+=sumIntegersTransitions(aNumberOfLedsSwitchOn60,iCurrentSecond, sumNumbersMod(iFinalSecond, -1, 60), -1);
			}

			iCurrentSecond=iFinalSecond;
			
			
			// sum switch on of final second transition
			lResult+=aNumberOfLedsSwitchOn60[iCurrentSecond];
			lResult+=aNumberOfLedsSwitchOn60[iCurrentMinute];
			lResult+=aNumberOfLedsSwitchOn60[iCurrentHour];
			

		}
		
		return lResult;
	}
	
}
