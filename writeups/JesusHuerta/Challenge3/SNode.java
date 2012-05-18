package Challenge3;

/**
 * <E> quiere decir que puede guardar cualquier objeto de tipo/clase E.
 * @author isegura
 *
 * @param <E>
 */
public class SNode<E> {
	public E element;
	public SNode<E> next;
	
	public SNode(){
		element=null;
		next=null;
	}
	
	public SNode(E obj, SNode<E> n){
		element=obj;
		next=n;
	}
	public SNode(E obj){
		element=obj;
		next=null;
	}
}
