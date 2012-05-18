/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.05.01
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 8
 *
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


public class Challenge8_md5 {
	private static class TablaConversion{
		private class CaracterEnlazado{
			//Es más rápido en este caso implementar con una cadena enlazada en vez de un string (~1500%)
			private char caracter;
			private CaracterEnlazado next;
			private CaracterEnlazado tempFinal = null; //Solo valido tras un clone
			
			CaracterEnlazado(char c){
				this.caracter = c;
				this.next = null;
			}

			public CaracterEnlazado clone(){
				CaracterEnlazado punteroLectura = this;
				CaracterEnlazado inicio = new CaracterEnlazado(this.caracter);
				CaracterEnlazado actual = inicio;
				//inicio.tempFinal = actual; como minimo tienen 2 caracteres las cadenas (cabecera+1)
				while(punteroLectura.next != null){
					punteroLectura = punteroLectura.next;
					actual.next = new CaracterEnlazado(punteroLectura.caracter);
					actual = actual.next;
					inicio.tempFinal = actual;
				}
				
				return inicio;
			}
			
			public String toString(){
				StringBuffer ret = new StringBuffer();
				CaracterEnlazado cE = this.next; //descontamos cabecera
				
				while (cE!= null){
					ret.append(cE.caracter);
					cE = cE.next;
				}
				return ret.toString();
			}
		}
		
		private CaracterEnlazado cEdesdeString(String s){ 
			if(s.length() == 0)
				return null;
			
			CaracterEnlazado inicio = new CaracterEnlazado(s.charAt(0));
			CaracterEnlazado actual = inicio;
			for(int i=1; i<s.length();i++){
				actual.next = new CaracterEnlazado(s.charAt(i));
				actual = actual.next;
			}

			return inicio;
		}

		private CaracterEnlazado[] tabla = null; //resultados de transformaciones (char->string)
		private byte[][] cacheBytes = null;
		
		TablaConversion() {
			//inicializamos variables
			this.tabla = new CaracterEnlazado[256];
			this.cacheBytes = new byte[256][];
		}
		
		byte[] getBytes(char c){
			byte[] ret = cacheBytes[c];
			if (ret!=null) //Si hay resultado, devolverlo
				return ret;
			
			//Si no, lo calculamos, lo guardamos en la caché y lo devolvemos
			CaracterEnlazado cE = tabla[c];
			if (cE!=null)
				ret = cE.toString().getBytes();
			else
				ret = (""+c).getBytes();
			
			cacheBytes[c] = ret;
			return ret;
		}
		
		void merge(String s){
			CaracterEnlazado[] temporal = new CaracterEnlazado[256];
			//analizamos la entrada s y guardamos en temporal las transformaciones temporales
			for(int i =0; i < s.length(); i++){
				int j;
				for(j=i+3;j<s.length();j++){
					if (s.charAt(j)==',')
						break;
				}
				
				temporal[s.charAt(i)]= cEdesdeString(">"+s.substring(i+3, j));
				i=j;
			}
			
			//Unificamos las transformaciones temporales en tabla
			for(char c = 0; c< tabla.length; c++){
				//PAra cada caracter (indice) de tabla
				if (tabla[c] == null){
					//Comprobamos si hay una transformación para c,
					//Si no la hay, buscamos en temporal, y si está
					// en temporal, la almacenamos
					if (temporal[c]!=null)
						tabla[c]=temporal[c].clone();
					
				}else{
					//Como hay una transformación en c,
					//la transformación que hay que guardar es 
					//aplicar las transformaciones de temporal
					//a la que ya tenemos
					CaracterEnlazado cadena = tabla[c];
					while(cadena.next != null){
						CaracterEnlazado siguienteCaracter = cadena.next;
						//a cada caracter de la transformación de c
						//se la aplicamos
						if (temporal[siguienteCaracter.caracter]!=null){
							CaracterEnlazado subcadena = temporal[siguienteCaracter.caracter].clone();
						
							cadena.next = subcadena.next;
							cadena = subcadena.tempFinal;
							cadena. next = siguienteCaracter.next;
						}else
							cadena = siguienteCaracter;
					}
				}
			}
		}
	}

	public static void main(String[] args) {
		//long begin = System.currentTimeMillis();

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String original = null;
		try {
			original = reader.readLine();
		} catch (IOException e) {
			System.exit(-1);
		}
		if(original == null)
			System.exit(-1);
		
		//Se van a unir todas las transformaciones en una sola, para eso se usa la clase TablaConversion
		TablaConversion t = new TablaConversion();

		String s = null;
		try {
			while((s= reader.readLine())!= null)
				t.merge(s); //Añadimos reglas a t
		} catch (IOException e) {
			System.exit(-1);
		}
		
		//long tiempoReglas = System.currentTimeMillis();
		//System.err.println(">tiempo en procesar las reglas:"+(tiempoReglas-begin));
		
		//MD5 String -> String por partees
		String res = "";
        try {
            MessageDigest alg = MessageDigest.getInstance("MD5");
            alg.reset();

    		//Para cada caracter de c, lo transformamos en los bytes de acuerdo a las reglas y lo introducimos en el MD5
    		for (int i = 0; i< original.length();i++)
    			alg.update(t.getBytes(original.charAt(i)));
    		
            byte[] md5 = alg.digest();
            for (int i = 0; i < md5.length; i++) {
            	String tmp = Integer.toHexString(0xFF & md5[i]);
                if (tmp.length() == 1)
                    res += "0" + tmp;
                else
                    res += tmp;
            }
        }catch(NoSuchAlgorithmException e){
        	System.exit(-1);
        }  
        System.out.println(res);
        //System.err.println(">tiempo en procesar el texto:"+(System.currentTimeMillis()-tiempoReglas));
	}
}
