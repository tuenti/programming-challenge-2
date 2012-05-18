package Challenge3;
public class DList<E> implements IDList<E>{
	/**Nodo centinela cuyo propiedad next apunta al primer nodo de la lista*/
	public DNode<E> header;
	/**Nodo centinela cuyo propiedad prev apunta al último nodo de la lista*/
	public DNode<E> tailer;
	public SNode<E> front, tail;
	public int size;
	
	/**
	 * Crea una lista vacía. Para ello 
	 * inicializa los dos nodos centinelas
	 */
	public DList() {
		header=new DNode<E>();
		tailer=new DNode<E>();
		//Se apuntan el uno al otro
		header.next=tailer;
		tailer.prev=header;
		size=0;
	}
	
	/**
	 * Devuelve true si la lista está vacía, false en otro caso.
	 * @return
	 */
	public boolean isEmpty() {
		return (size==0);
	}
	
	/**
	 * devuelva el nodo que contiene el elemento es. Complejidad O(n)
	 * @param v
	 */
	public DNode<E> search(E e) {
		if (e==null) {
			System.out.println("No se puede buscar null");
			return null;
		}
		DNode<E> aux=header;
		while (aux!=tailer && aux.element!=e) {
			aux=aux.next;
		}
		if (aux==tailer){
		System.out.println("no existe...");
		return null;
		}else{
		return aux;
		}
	}

	/**
	 * ESte método inserta el nodo newNodo al principio de la lista.
	 * Complejidad O(1), porque el método ejecuta un número constante de instrucciones.
	 * @param newNodo
	 */
	public  void addFirst(DNode<E> newNodo) {
		if (newNodo==null) {
			System.out.println("El nodo es nulo, no podemos insertarlo!!!");
			return; //salimos del método
		}
		
		DNode<E> v=header.next;
		//El nuevo nodo deberá apuntar al primer nodo de la lista
		newNodo.next=v;
		v.prev=newNodo;
		//Ahora hacemos que el primer nodo sea newNodo
		header.next=newNodo;
		newNodo.prev=header;
		
		//Incrementamos el tamaño de la lista
		size++;
		
	}
	
	/**
	 * ESte método inserta el nodo newNodo al final de la lista.
	 * Complejidad O(1), porque el método ejecuta un número constante de instrucciones.
	 * @param newNodo
	 */
	public  void addLast(DNode<E> newNodo) {
		if (newNodo==null) {
			System.out.println("El nodo es nulo, no podemos insertarlo!!!");
			return; //salimos del método
		}
		
		DNode<E> v=tailer.prev;
		v.next=newNodo;
		newNodo.prev=v;
		newNodo.next=tailer;
		tailer.prev=newNodo;
		
		//Incrementamos el tamaño de la lista
		size++;
		
	}
	
	
	/**
	 * Inserta después del nodo v. Complejidad O(1)
	 * @param v
	 * @param newNodo
	 */
	public void addAfter(E e, E n) {
	DNode<E> v = search(e);
	DNode<E> newNodo = new DNode<E>(n);
	if (v!=null){
	DNode<E> u = v.next;
	newNodo.prev=v;
	newNodo.next=u;
	v.next=newNodo;
	u.prev=newNodo;
	size++;
	}
	}
	
	/**
	 * Inserta antes del nodo v. Complejidad O(1)
	 * @param v
	 * @param newNodo
	 */
	public void addBefore(E e, E n) {
		DNode<E> v = search(e);
		DNode<E> newNodo = new DNode<E>(n);
		if(v!=null){ 
			DNode<E> u=v.prev;
			newNodo.prev=u;
			newNodo.next=v;
			u.next=newNodo;
			v.prev=newNodo;
			size++;
		}
	}
	
	/**
	 * Borra el primer elemento de la lista. Complejidad O(1).
	 */
	public void removeFirst() {
		if (isEmpty()) {
			System.out.println("La lista ya está vacia!!!");
			return; //salimos del método
		}
		
		DNode<E> v = header.next;
		DNode<E> u = v.next;
		//primerNodo debe pasar a ser el siguiente nodo. 
		header.next = u;
		u.prev=header;
		size--;
	}
	/**
	 * Borra el último nodo de la lista. Complejidad O(1).
	 */
	public void removeLast() {
		if (isEmpty()) {
			System.out.println("La lista ya está vacia!!!");
			return; //salimos del método
		}
		
		DNode<E> v=tailer.prev;
		DNode<E> u=v.prev;
		tailer.prev=u;
		u.next=tailer;
		size--;
	}	
	public E dequeue() {
		if (isEmpty()) {
			System.out.println("Queue is empty");
			return null;
		}
		E temp=front.element;
		front=front.next;
		size--;
		if (size==0) tail=null;
		return temp;
	}
	
	
	public void enqueue(E e) {
		SNode<E> newNodo=new SNode<E>(e,null);
		if (isEmpty()) front=newNodo;
		else tail.next=newNodo;
		tail=newNodo;
		size++;
	}
	
	public E front() {
		if (isEmpty()) {
			System.out.println("Queue is empty");
			return null;
		}
		return front.element;
	}
	public int size() { return (size); }
}
