package es.felixcoto.tuenti;

import java.util.Scanner;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {
			Scanner sc=new Scanner(System.in);
			int iNumSoftwareReports=sc.nextInt();
			int iNumUnknownReports=sc.nextInt();
			int iDifferentSystemCalls=sc.nextInt();
			
			
			
			Perceptron objPerceptron=new Perceptron(iDifferentSystemCalls, ReportType.values().length);
			
			for (int iNumReport=0;iNumReport<iNumSoftwareReports;iNumReport++){
				String sReportTypeCode=sc.next();
				ReportType objReportType=ReportType.lookup(sReportTypeCode);
				if (objReportType==null){
					throw new Exception(String.format("Report type %s unknown", sReportTypeCode));
				}
				int [] intValues=readIntArray(sc, iDifferentSystemCalls);
				objPerceptron.addTestCase(intValues, objReportType.getExpectedPerceptronResult());
				
				sc.nextLine();
				
			}
			
			objPerceptron.processLearning();

			long lMalwareSystemCalls=0;
			
			for (int iCurrentUnknownReport=0;iCurrentUnknownReport<iNumUnknownReports;iCurrentUnknownReport++){
				int [] intValues=readIntArray(sc, iDifferentSystemCalls);
				int [] iPerceptronResult=objPerceptron.processPerceptron(intValues);
				if (ReportType.MALWARE.isPerceptronResultEqual(iPerceptronResult)){
					lMalwareSystemCalls+=sumIntArray(intValues);
				}
			}
			System.out.println(lMalwareSystemCalls);
			
			
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	
	private static int[] readIntArray(Scanner sc,int iArrayLength){
		int[] result=new int[iArrayLength];
		for (int i=0;i<iArrayLength;i++){
			result[i]=sc.nextInt();
		}
		return result;
	}
	
	private static long sumIntArray(int[] intArray){
		long result=0;
		for (int i=0;i<intArray.length;i++){
			result+=intArray[i];
		}
		return result;
	}
	
	
}
