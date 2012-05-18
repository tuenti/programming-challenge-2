package es.felixcoto.tuenti;

public class QuickTester {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String [] test=new String[]{"HI 20","tu", "PrUeB000","0"," 0","U0u"};
		for (String currentTest : test) {
			System.out.println(currentTest+":"+Main.calculateDelay(currentTest));
		}
	}

}
