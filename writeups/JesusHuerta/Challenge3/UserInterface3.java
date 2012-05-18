package Challenge3;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
/* 
   JESUS HUERTA ARRABAL
   DESARROLLADOR DE APLICACIONES INFORMÁTICAS
 
 */
public class UserInterface3 {
    public void run() throws IOException{
    	BigInteger interacciones = new BigInteger("0");
//    	String line;
    	String line[] = {"29","5","12","10","17","15","21","28","1","13"};
    	EvilTrader ObjetoEvil = new EvilTrader();
//        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
//        do{
//        	line = reader.readLine();
        	for (int i=0; i<line.length; i++){
//        	if  (line != null && !line.trim().equals("")){
//        		ObjetoEvil.insert(new Stock(Integer.parseInt(line), interacciones)); //Insertar en la cola y el vector
         	ObjetoEvil.insert(new Stock(Integer.parseInt(line[i]), interacciones)); //Insertar en la cola y el vector
        		interacciones = interacciones.add(new BigInteger("1"));
         	}
//        }while(line != null);
        ObjetoEvil.ordenar();  
        ObjetoEvil.search();
    	ObjetoEvil.result();
    }
}