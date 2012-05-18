/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.27
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 1
 *
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Challenge1_keypad {
	//La tecla 10 es capsLock
	private static int[] teclaToFila = {3,0,0,0,1,1,1,2,2,2,3};
	private static int[] teclaToColumna = {1,0,1,2,0,1,2,0,1,2,2};
	private static final int TIEMPO_VERTICAL = 300;
	private static final int TIEMPO_HORIZONTAL = 200;
	private static final int TIEMPO_DIAGONAL = 350;
	private static final int TIEMPO_PULSACION = 100;
	private static final int TIEMPO_ESPERA_MISMA_TECLA = 500;
	private static char[][] teclas = {
		{				 '0'},
		{' ',			 '1'},
		{'A','B','C',	 '2'},
		{'D','E','F',	 '3'},
		{'G','H','I',	 '4'},
		{'J','K','L',	 '5'},
		{'M','N','O',	 '6'},
		{'P','Q','R','S','7'},
		{'T','U','V',	 '8'},
		{'W','X','Y','Z','9'},
	};
	private static int charToTecla[] = null;
	private static int charToPulsacionesExtra[] = null; //Se presupone una pulsación por tecla
	
	private static void completarCharToTecla(){
		//Se inicializan y completan las tablas de acceso rápido
		charToTecla = new int[256];
		charToPulsacionesExtra = new int[256];
		
		for (int i = 0; i<charToTecla.length; i++)
			charToTecla[i] = -1; //Inicializamos para reconocer caracteres no en keypad
		
		for (int i = 0; i<teclas.length; i++){
			for(int j = 0; j< teclas[i].length; j++){
				char escogido = teclas[i][j];
				charToTecla[escogido] = i;
				charToPulsacionesExtra[escogido] = j; //Se presupone una pulsación
				charToTecla[Character.toLowerCase(escogido)] = i;
				charToPulsacionesExtra[Character.toLowerCase(escogido)] = j; //Se presupone una pulsación
			}
		}
	}
	
	private static int tiempoMovimientoYUnaPulsacion(int teclaActual, int teclaDestino){
		if (teclaActual == teclaDestino)//Misma tecla
			return TIEMPO_ESPERA_MISMA_TECLA + TIEMPO_PULSACION;
		
		//Se calcula la distancia en filas, columnas y diagonal y se multiplica por el tiempo correspondiente
		int distanciaFilas = Math.abs(teclaToFila[teclaDestino]-teclaToFila[teclaActual]); 
		int distanciaColumnas = Math.abs(teclaToColumna[teclaDestino]-teclaToColumna[teclaActual]);	
		int distanciaDiagonal = Math.min(distanciaFilas,distanciaColumnas);
		distanciaFilas -= distanciaDiagonal;
		distanciaColumnas -= distanciaDiagonal;
		
		return distanciaDiagonal * TIEMPO_DIAGONAL + distanciaFilas * TIEMPO_VERTICAL + distanciaColumnas * TIEMPO_HORIZONTAL + TIEMPO_PULSACION;
	}
	
	public static void main(String[] args) {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		int numero_casos = 0;
		
		try {
			numero_casos = Integer.parseInt(reader.readLine());
		} catch (Exception e){
			System.exit(-1);
		}
		
		completarCharToTecla(); //Crear tablas de acceso rápido
		
		for(;numero_casos>0; numero_casos--){
			String linea = null;
			try {
				linea = reader.readLine();
			} catch (IOException e) {
				continue;
			}
			
			if (linea == null){
				//Final de fichero inesperado
				continue;
			}
			
			int teclaActual = 0;
			int tiempo = 0;
			boolean capsLock = false;
			int indice_caracter;
			
			for (indice_caracter = 0; indice_caracter<linea.length();indice_caracter++){
				char caracter_leido = linea.charAt(indice_caracter);
				if (caracter_leido > 255) //Caracter fuera de rango
					break;
				
				int teclaDestino = charToTecla[caracter_leido];
				if (teclaDestino<0) //Caracter no en keypad
					break;
				
				if (Character.isLetter(caracter_leido) && (Character.isUpperCase(caracter_leido) != capsLock)){
					//Si es letra y necesitamos pulsar CapsLock vamos a la tecla 10 y pulsamos
					tiempo += tiempoMovimientoYUnaPulsacion(teclaActual, 10);
					teclaActual = 10;
					capsLock = !capsLock;
				}
				
				tiempo += (tiempoMovimientoYUnaPulsacion(teclaActual, teclaDestino)+ charToPulsacionesExtra[caracter_leido] * TIEMPO_PULSACION);
				teclaActual = teclaDestino;
			}
		
			if (indice_caracter == linea.length()) //Se ha procesado toda la cadena
				System.out.println(tiempo);
			else
				System.out.println();
		}
	}
}
