package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

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
				String sConfigTestLine=bf.readLine();
				Scanner sc=new Scanner(sConfigTestLine);
				int iNumberOfRaces=sc.nextInt();
				int iNumberOfKarts=sc.nextInt();
				int iNumberOfGroups=sc.nextInt();
				int [] iSizeOfGroups=new int[iNumberOfGroups];
				String sSizeOfGroupsLine=bf.readLine();
				Scanner scGroups=new Scanner(sSizeOfGroupsLine);
				for (int i=0;i<iNumberOfGroups;i++){
					iSizeOfGroups[i]=scGroups.nextInt();
				}
				
				int iNumberOfLiters=calculateLiters(iNumberOfRaces,iNumberOfKarts, iSizeOfGroups );
				System.out.println(iNumberOfLiters);
				currentNumberOfTest++;
			}

		} catch (Exception e) {
			e.printStackTrace();
		}


	}

	private static int calculateLiters(int iNumberOfRaces, int iNumberOfKarts, int[] aSizeOfGroups) {
		int iResult=0;
		int iRacesLeft=iNumberOfRaces;
		
		// Initialize queue
		List<Integer> objQueue=new LinkedList<Integer>();
		for (int i=0;i<aSizeOfGroups.length;i++){
			objQueue.add(aSizeOfGroups[i]);
		}
		
		// Cache of races to detect pattern
		Map<List<Integer>,Integer> objCacheOfRace=new HashMap<List<Integer>, Integer>();
		
		// while are races to do
		while (iRacesLeft>0){
			
			if (!objCacheOfRace.containsKey(objQueue)){
				// new type of race
				int iKartsFree=iNumberOfKarts;
				int iCurrentQueuePosition=0;
				//configure race
				while (iKartsFree>0&&
						iCurrentQueuePosition<objQueue.size()&&
						iKartsFree>=objQueue.get(iCurrentQueuePosition)){
					int iCurrentGroup=objQueue.get(iCurrentQueuePosition);
					iKartsFree-=iCurrentGroup;
					iCurrentQueuePosition++;
				}
				
				// Save race configuration to detect pattern
				List<Integer> objOldQueue=new LinkedList<Integer>(objQueue);
				objCacheOfRace.put(objOldQueue, iCurrentQueuePosition);
				
				// Cycle Queue for next race
				if (iCurrentQueuePosition!=objQueue.size()){
					for (int i=0;i<iCurrentQueuePosition;i++){
						int iCurrentGroup=objQueue.remove(0);
						objQueue.add(iCurrentGroup);
					}
				}
				// race configured, calculate liters
				iResult+=iNumberOfKarts-iKartsFree;
				

				// Mark race done
				iRacesLeft--;
			}else{
				// Pattern detected
				List<Integer> objKartsUsedByPatternSize=new ArrayList<Integer>(aSizeOfGroups.length);
				int iTotalPatternKartsUsed=0;
				List<Integer> objCurrentQueue=new LinkedList<Integer>(objQueue);
				Set<List<Integer>> objUsedQueue=new HashSet<List<Integer>>();
				
				//Build pattern
				while (!objUsedQueue.contains(objCurrentQueue)&&objKartsUsedByPatternSize.size()<iRacesLeft){
					int iUsedGroups=objCacheOfRace.get(objCurrentQueue);
					int iCurrentRace=0;
					List<Integer> objOldQueue=new LinkedList<Integer>(objCurrentQueue);
					objUsedQueue.add(objOldQueue);
					for (int i=0;i<iUsedGroups;i++){
						int iCurrentGroup=objCurrentQueue.remove(0);
						iCurrentRace+=iCurrentGroup;
						objCurrentQueue.add(iCurrentGroup);
					}
					objKartsUsedByPatternSize.add(iCurrentRace);
					iTotalPatternKartsUsed+=iCurrentRace;
				}
				
				//Apply pattern
				int iNumOfCycles=iRacesLeft/objKartsUsedByPatternSize.size();
				iResult+=iNumOfCycles*iTotalPatternKartsUsed;
				
				int iRemainder=iRacesLeft%objKartsUsedByPatternSize.size();
				for (int i=0;i<iRemainder;i++){
					iResult+=objKartsUsedByPatternSize.get(i);
				}
				
				// All races done
				iRacesLeft=0;
			}
		}
		
		return iResult;
	}
	

}
