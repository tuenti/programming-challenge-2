package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.InputStreamReader;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.List;

public class Main {
	private static final int BUF_SIZE=11000000;
	private static final int BUF_DUMP=10000000;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			String sQueue=bf.readLine();
			String sLine=bf.readLine();
			List<String> listConfig=new ArrayList<String>();
			while (sLine!=null){
				listConfig.add(sLine);
				sLine=bf.readLine();
			}
			bf.close();
			CloningMachine objCloningMachine=new CloningMachine(listConfig);
			MessageDigest objMessageDigest=MessageDigest.getInstance("MD5");
			objMessageDigest.reset();

			
			ByteArrayOutputStream ba=new ByteArrayOutputStream(BUF_SIZE);
			for (int i=0;i<sQueue.length();i++){
				String sResultPerson=objCloningMachine.processPerson(sQueue.charAt(i));
				ba.write(sResultPerson.getBytes());
				if (ba.size()>BUF_DUMP){
					objMessageDigest.update(ba.toByteArray());
					ba.reset();
				}
			}
			if (ba.size()>0){
				objMessageDigest.update(ba.toByteArray());
			}
			
			
			byte[] objByteDigest=objMessageDigest.digest();
			StringBuilder sb=new StringBuilder();
			for (byte b : objByteDigest) {
				sb.append(Integer.toHexString(0xFF & b));
			}

			System.out.println(sb.toString());
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

}
