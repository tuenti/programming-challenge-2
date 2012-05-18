package es.felixcoto.tuenti;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CodingErrorAction;

public class Main {
	private static final String ERROR_TEXT="Error!";

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			BufferedReader bf=new BufferedReader(new InputStreamReader(System.in));
			
			
			//Charset to decode
			Charset objASCIICharset=Charset.forName("US-ASCII");

			String sLine;
			while ((sLine=bf.readLine())!=null){
				// current Hamming block
				boolean[] aCurrentBlock=new boolean[7];
				int iCurrentBitDataBlock=0;
				// current character
				int iCurrentBitCharacter=0;
				int iCurrentCharByte=0;
				// buffer for byte decoded
				ByteArrayOutputStream bo=new ByteArrayOutputStream();

				boolean bLineError=false;
				int iCurrentCharNumber=0;
				while (iCurrentCharNumber<sLine.length()&&!bLineError){

					char cCurrentChar=sLine.charAt(iCurrentCharNumber);
					//check '1' or '0'
					switch(cCurrentChar){
					case '0':
						if (!bLineError){

							aCurrentBlock[iCurrentBitDataBlock]=false;
							iCurrentBitDataBlock++;
						}
						break;

					case '1':
						if (!bLineError){

							aCurrentBlock[iCurrentBitDataBlock]=true;
							iCurrentBitDataBlock++;
						}
						break;
					default:
						bLineError=true;

					}
					// complete Hammimg block
					if (iCurrentBitDataBlock>=aCurrentBlock.length&&!bLineError){
						boolean[] aDataDecoded=Hamming74.decodeData(aCurrentBlock);
						for (int i=0;i<aDataDecoded.length;i++){
							iCurrentCharByte=iCurrentCharByte<<1;
							if (aDataDecoded[i]){
								iCurrentCharByte=iCurrentCharByte|0x1;
							}
							iCurrentBitCharacter++;
						}
						iCurrentBitDataBlock=0;
						// Byte complete, store in buffer
						if (iCurrentBitCharacter>=7){
							bo.write(iCurrentCharByte);
							iCurrentCharByte=0;
							iCurrentBitCharacter=0;
						}
					}
					iCurrentCharNumber++;
				}

				String sResult="";
				// if there is not pending data and all input is correct
				// decode data to char
				if (iCurrentBitCharacter==0&&iCurrentBitDataBlock==0&&!bLineError){
					if (bo.size()>0){
						CharsetDecoder objDecoder=objASCIICharset.newDecoder();
						objDecoder.onMalformedInput(CodingErrorAction.REPORT);
						ByteBuffer byteBuf=ByteBuffer.wrap(bo.toByteArray());
						try {
							CharBuffer chBuf=objDecoder.decode(byteBuf);
							sResult=chBuf.toString();
						} catch (CharacterCodingException e) {
							// Byte not valid in ASCII
							sResult=ERROR_TEXT;
						}
					}else{
						sResult=ERROR_TEXT;
					}

				}else{
					sResult=ERROR_TEXT;
				}
				System.out.println(sResult);

			}
		} catch (Exception e) {
			e.printStackTrace();
		}


	}

}
