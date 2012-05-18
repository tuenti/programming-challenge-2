package es.felixcoto.tuenti;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public enum ReportType {
	SAFE("S",new int[]{1,0}),MALWARE("M",new int[]{0,1});

	private final String sLookupCode;
	private final int[] expectedPerceptronResult;
	private ReportType(String sLookupCode,int[] expectedPerceptronResult) {
		this.sLookupCode=sLookupCode;
		this.expectedPerceptronResult=expectedPerceptronResult;
	}

	private static Map<String, ReportType> lookupTable=new HashMap<String, ReportType>();

	public static ReportType lookup(String sCode){
		return lookupTable.get(sCode);
	}

	static{
		for (ReportType objReportType : ReportType.values()) {
			lookupTable.put(objReportType.getsLookupCode(), objReportType);
		}
		lookupTable=Collections.unmodifiableMap(lookupTable);
	}
	
	
	public String getsLookupCode() {
		return sLookupCode;
	}


	public int[] getExpectedPerceptronResult() {
		return expectedPerceptronResult;
	}

	public boolean isPerceptronResultEqual(int[] iPerceptronResult){
		boolean bResult=true;
		int i=0;
		while (bResult&&i<expectedPerceptronResult.length){
			bResult=expectedPerceptronResult[i]==iPerceptronResult[i];
			i++;
		}
		return bResult;
	}
	
}
