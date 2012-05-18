package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			List<Long> listOfStocksSamples=new ArrayList<Long>();
			String currentLine=bf.readLine();
			while (currentLine!=null){
				listOfStocksSamples.add(new Long(currentLine));
				currentLine=bf.readLine();
			}
			
			int iBuyTime=0;
			int iSellTime=0;
			long lGain=0;
			
			
			int iCurrentIterationBuyTime=0;
			long lCurrentIterationBuyPrice=listOfStocksSamples.get(0);
			int iCurrentIterationSellTime=0;
			long lCurrentIterationGain=0;
			int iCurrentSellTime=0;
			while (iCurrentSellTime<listOfStocksSamples.size()-1){
				iCurrentSellTime++;
				long lCurrentSellPrice=listOfStocksSamples.get(iCurrentSellTime);
				if (lCurrentSellPrice<lCurrentIterationBuyPrice){
					
					if (lCurrentIterationGain>lGain){
						iBuyTime=iCurrentIterationBuyTime;
						iSellTime=iCurrentIterationSellTime;
						lGain=lCurrentIterationGain;
					}
					
					iCurrentIterationBuyTime=iCurrentSellTime;
					iCurrentIterationSellTime=iCurrentSellTime;
					lCurrentIterationBuyPrice=lCurrentSellPrice;
					
					lCurrentIterationGain=0;

				}else{
					long lCurrentGain=lCurrentSellPrice-lCurrentIterationBuyPrice;
					
					if (lCurrentGain>lCurrentIterationGain){
						iCurrentIterationSellTime=iCurrentSellTime;
						lCurrentIterationGain=lCurrentGain;
					}
				}
			}
			System.out.println(String.format("%d %d %d",iBuyTime*100,iSellTime*100,lGain));
			
			
			
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
