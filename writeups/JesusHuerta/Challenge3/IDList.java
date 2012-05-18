package Challenge3;
public interface IDList<E> {

	public boolean isEmpty() ;
	
	public  void addFirst(DNode<E> newNodo) ;
	
	public void addAfter(E e, E n) ;
	
	public void addBefore(E e, E n) ;
	
	public void removeLast() ;
	
	public E dequeue() ;
	
	public void enqueue(E e) ;

	public E front() ;

}
