/* Autor: José Mª Pérez Ramos
 * Fecha: 2012.04.28
 * 
 * Programa de prueba para el segundo concurso de
 * de programación de Tuenti, prueba 5
 *
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class Challenge5_Clocks {
	//Reloj viejo
	private static final int[] nLeds = { //Número de LEDs por dígito
		6,	//0
		2,	//1
		5,	//2
		5,	//3
		4,	//4
		5,	//5
		6,	//6
		3,	//7
		7,	//8
		6	//9
	};
	////Reloj nuevo
	private static final int[] nLedsNuevosDesdeAnteriorGeneral = { //Número de LEDs que se encienden desde el anterior
		1,	//0 (desde 9)
		0,	//1 (desde 0)
		4,	//2 (desde 1)
		1,	//3 (desde 2)
		1,	//4 (desde 3)
		2,	//5 (desde 4)
		1,	//6 (desde 5)
		1,	//7 (desde 6)
		4,	//8 (desde 7)
		0	//9 (desde 8)
	};
	private static final int nLedsNuevosDesde235 = 2; //Número de LEDs que se encienden desde el anterior(2,3,5) para el 0 
	
	//Diferencia entre relojes
	private static int[] nLedsDiferencia0_9 = null;
	private static int nLedsDiferencia0_235; 
		//Solo se necesita saber cuál es la diferencia de leds al encender 
		//el 0 en caso de que el último haya sido 2, 3,5 (que coincide)
	private static int nLedsDiaDiferencia = 0;

	private static int[] nLedsDiferenciaDesde0 = null;
	
	private static int incrementarEnUnoRDiferencia(int[] reloj){
		//Incrementa reloj en 1 y devuelve la ganancia en leds del viejo respecto del nuevo
		
		int ret = 0;
		int i;
		for (i=5;i>=0;i--){
			if (reloj[i] == 9){
				reloj[i]=0;
				ret += nLedsDiferencia0_9[0];
			}else if((reloj[i] == 2 && i==0)||(reloj[i] == 5 && i%2==0)||(i==1 && reloj[0]>=2 && reloj[1] >=3)){
				reloj[i]=0;
				ret += nLedsDiferencia0_235;
			}else{
				reloj[i]++;
				ret += nLedsDiferencia0_9[reloj[i]];
				break;
			}
		}
		i--;
		for(; i>=0; i--)
			ret += nLeds[reloj[i]];
		
		return ret;
	}
	
	private static void completarValoresDiferencia(){
		nLedsDiferencia0_9 = new int[10];
		
		for(int i=0; i<nLeds.length;i++ )
			nLedsDiferencia0_9[i] = nLeds[i]-nLedsNuevosDesdeAnteriorGeneral[i];
			
		nLedsDiferencia0_235 = nLeds[0]-nLedsNuevosDesde235;
		
		//Completamos la tabla de leds que hacen falta para alcanzar el segundo X desde 000000
		nLedsDiferenciaDesde0 = new int[24*60*60];
		int[] reloj = {0,0,0,0,0,0};
		nLedsDiaDiferencia =0;
		for(int i =0; i <24*60*60;i++){
			nLedsDiferenciaDesde0[i] = nLedsDiaDiferencia;
			nLedsDiaDiferencia+=incrementarEnUnoRDiferencia(reloj);
		}
	}

	private static long ledsONRelojDiferencia(long dias, int segHoraInicio ,int segHoraFin){
		/* Se calcula los leds que hacen falta para llegar desde 000000 hasta horaFin
		 * Se calcula los leds que hacen falta para llegar desde horaInicio hasta 000000 (todos los de un día menos los desde 000000 hasta horaInicio)
		 * Añadimos los días teniendo en cuenta que tenemos que descontar un día
		 */
		return nLedsDiferenciaDesde0[segHoraFin] + (nLedsDiaDiferencia-nLedsDiferenciaDesde0[segHoraInicio]) + (dias-1)*nLedsDiaDiferencia;
	}

	//GENERAL
	private static int crearReloj(String fecha){
		//"yyyy-MM-dd HH:mm:ss"
		int[] reloj = new int[6];
		
		reloj[0]=fecha.charAt(11)-'0';
		reloj[1]=fecha.charAt(12)-'0';
		reloj[2]=fecha.charAt(14)-'0';
		reloj[3]=fecha.charAt(15)-'0';
		reloj[4]=fecha.charAt(17)-'0';
		reloj[5]=fecha.charAt(18)-'0';

		return ((reloj[0]*10+reloj[1])*60 + (reloj[2]*10 + reloj[3])) *60+(reloj[4]*10 + reloj[5]);
	}
	
	private static long calcularGanancia(String fechas){
		Date fechaInicio;
		Date fechaFin;
		int relojInicio = crearReloj(fechas.substring(0, 19));
		int relojFin = crearReloj(fechas.substring(22, 41));
		
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try {
			fechaInicio = format.parse(fechas.substring(0, 19));
			fechaFin = format.parse(fechas.substring(22, 41));
		}catch(ParseException e) {
			return 0;
		}
		
		Calendar calendar1 = Calendar.getInstance();
		Calendar calendar2 = Calendar.getInstance();
		calendar1.setTime(fechaInicio);
		calendar2.setTime(fechaFin);
		long dias = (calendar2.getTimeInMillis() - calendar1.getTimeInMillis()) / (24 * 60 * 60 * 1000);
		
		if (fechaInicio.before(fechaFin)){
			return ledsONRelojDiferencia(dias,relojInicio,relojFin);
		}else{
			return ledsONRelojDiferencia(-1*dias,relojFin,relojInicio);
		}
	}
	
	public static void main(String[] args) {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		completarValoresDiferencia();
		
		String linea = null;
		try {
			linea = reader.readLine();
		} catch (IOException e) {
			System.exit(-1);
		}

		while(linea != null && linea.length() >= 41){
			System.out.println(calcularGanancia(linea));
			try {
				linea = reader.readLine();
			} catch (IOException e) {
				System.exit(-1);
			}
		}
	}
}
