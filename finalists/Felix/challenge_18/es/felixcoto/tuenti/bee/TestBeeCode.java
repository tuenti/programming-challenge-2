package es.felixcoto.tuenti.bee;

import java.io.InputStream;

public class TestBeeCode {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		InputStream in=Thread.currentThread().getContextClassLoader().getResourceAsStream("program.bee");
		BeeMachine objBeeMachine=new BeeMachine(in);
		String sResult=objBeeMachine.process();
		System.out.println(sResult);
		
	}

}
