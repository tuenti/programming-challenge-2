package es.felixcoto.tuenti;

import java.util.ArrayList;
import java.util.List;

public class Perceptron {
	private static final double BIAS=0.7;
	private static final double DELTA=0.2;
	
	double[][]weigths;
	int iNumberOfInputNeurons;
	int iNumberOfOutputNeurons;
	
	List<TestCase> objListCases;
	
	/**
	 * @param objNumberOfInputNeurons
	 * @param objNumberOfOutputNumbers
	 */
	public Perceptron(int objNumberOfInputNeurons, int objNumberOfOutputNumbers) {
		iNumberOfInputNeurons = objNumberOfInputNeurons;
		iNumberOfOutputNeurons = objNumberOfOutputNumbers;
		weigths=new double[iNumberOfInputNeurons][iNumberOfOutputNeurons];
		objListCases=new ArrayList<Perceptron.TestCase>();
	}
	
	public int[] processPerceptron(int[] iPattern){
		if (iPattern.length!=iNumberOfInputNeurons){
			throw new IllegalArgumentException("Pattern size incorrect");
		}
		
		int [] iResult=new int[iNumberOfOutputNeurons];
		for (int i=0;i<iNumberOfOutputNeurons;i++){
			double dPartialResult=0;
			for (int j=0;j<iNumberOfInputNeurons;j++){
				dPartialResult+=weigths[j][i]*iPattern[j];
			}
			if (dPartialResult>BIAS){
				iResult[i]=1;
			}else{
				iResult[i]=0;
			}
		}
		return iResult;
		
	}
	
	public void addTestCase(int [] iPattern,int[] iExpectedResult){
		if (iPattern.length!=iNumberOfInputNeurons){
			throw new IllegalArgumentException("Pattern size incorrect");
		}
		if (iExpectedResult.length!=iNumberOfOutputNeurons){
			throw new IllegalArgumentException("ExpectedResult size incorrect");
		}
		TestCase objNewCase=new TestCase(iPattern, iExpectedResult);
		objListCases.add(objNewCase);
		
	}
	
	
	public void processLearning(){
		boolean bCompleted=false;
		while (!bCompleted){
			bCompleted=true;
			for (TestCase objCase : objListCases) {
				int [] iPattern=objCase.getPattern();
				int [] iExpectedResult=objCase.getExpectedResult();
				int [] iCurrentResult=processPerceptron(iPattern);
				for (int i=0;i<iNumberOfOutputNeurons;i++){
					if (iCurrentResult[i]!=iExpectedResult[i]){
						bCompleted=false;
						for (int j=0;j<iNumberOfInputNeurons;j++){
							weigths[j][i]=weigths[j][i]+(DELTA*iPattern[j]*(iExpectedResult[i]-iCurrentResult[i]));
						}
					}
				}
			}
		}
	}
	
	
	class TestCase{
		int[] iPattern;
		int[] iExpectedResult;
		/**
		 * @param objPattern
		 * @param objExpectedResult
		 */
		public TestCase(int[] objPattern, int[] objExpectedResult) {
			iPattern = objPattern;
			iExpectedResult = objExpectedResult;
		}
		public int[] getPattern() {
			return iPattern;
		}
		public int[] getExpectedResult() {
			return iExpectedResult;
		}
		
		
	}
}
