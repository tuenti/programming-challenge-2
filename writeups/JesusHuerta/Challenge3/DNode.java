package Challenge3;
/**
 * <E> quiere decir que puede guardar cualquier objeto de tipo/clase E.
 */
public class DNode<E> {
	public E element;
	public DNode<E> prev, next;
	
	public DNode(){
		prev=null;
		next=null;
	}
	public DNode(E objecto, DNode<E> p, DNode<E> n){
		element=objecto;
		prev=p;
		next=n;
	}
	public DNode(E objecto){
		element=objecto;
	}
}
