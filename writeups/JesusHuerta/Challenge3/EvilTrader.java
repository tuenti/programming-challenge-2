package Challenge3;
import java.math.BigInteger;
import java.util.*;
public class EvilTrader extends DList<Stock>{
	/*
	 * VARIABLES
	 */
	Vector<Stock> vector;
	Stock[] array;
	DList<Stock> cola;
	int gain;
	Stock aux1, aux2, aux, aux3;
	/*
	 * CONSTRUCTOR
	 */
	public EvilTrader(){
		cola = new DList<Stock>();
		vector=new Vector<Stock>();
		gain = 0;
	}
	/*
	 * METODOS
	 */
	void ordenar(){
		int b;
		do{
			b=0;
			for(int j=0; j<vector.size()-1; j++){
				if(vector.get(j).numero > vector.get(j+1).numero){
					Stock s = vector.get(j+1);
					vector.add(j+1, vector.get(j));
					vector.remove(j);
					vector.remove(j+1);
					vector.add(j, s);
					b++;
				}
			}			
		}while(b > 0);
	}
	public void insert(Stock elemento){
		cola.enqueue(elemento);
		vector.add(elemento);
	}
	public BigInteger buscar(int dato) {
		BigInteger inicio = BigInteger.valueOf(1);
		BigInteger fin = BigInteger.valueOf(vector.size()-1);
		BigInteger pos;
		while (inicio.compareTo(fin) <= 0) {
			pos = (inicio.add(fin)).divide(BigInteger.valueOf(2));
			if (vector.elementAt(pos.intValue()).numero == dato )
				return pos;
			else if ( vector.elementAt(pos.intValue()).numero < dato ) {
				inicio = pos.add(BigInteger.valueOf(1));
			} else {
				fin = pos.subtract(BigInteger.valueOf(1));
			}
		}
		return BigInteger.valueOf(0);
	}
	public void search(){
		aux1 = cola.front();
		aux2 = vector.elementAt(vector.size()-1);
		while (cola.size != 0) {
			int interaction = 1;
			int option = 0;
			aux = vector.get(vector.size()-1); //Me pongo al final del array que tiene el mayor número. 28 (posición 7 de la cola)
			aux3 = cola.front();
			while ((aux.numero - cola.front().numero) > 0 && option == 0){
				if ((aux.posicion.subtract(cola.front().posicion)).compareTo(BigInteger.valueOf(0)) > 0 && gain < vector.elementAt(vector.size()-1).numero - cola.front().numero){
					aux1 = cola.front();
					aux2 = aux;
					gain = vector.elementAt(vector.size()-1).numero - cola.front().numero;
					option = 1;
				}
				aux = vector.get(vector.size()-interaction);
				interaction++;
			}
			vector.removeElementAt(buscar(cola.front().numero).intValue());
			cola.dequeue();
		}
	}
	/*
	 * SOLUCION
	 */
	public void result(){
		System.out.println(aux1.posicion.multiply(BigInteger.valueOf(100)) + " " + aux2.posicion.multiply(BigInteger.valueOf(100)) + " " + gain);
	}
}