/*
 * Tuenti Programming Challenge 2
 * Challenge 7: The "Secure" Password
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.Map.Entry;

public class SecurePassword {

	private static class Adjacency<T> {
		private Set<T> _childs, _parents;

		public Set<T> getChilds() {
			return _childs;
		}

		public Set<T> getParents() {
			return _parents;
		}

		public Adjacency() {
			_childs = new HashSet<T>();
			_parents = new HashSet<T>();
		}

		public Adjacency<T> clone() {
			Adjacency<T> adj = new Adjacency<T>();
			adj._childs.addAll(_childs);
			adj._parents.addAll(_parents);
			return adj;
		}

		@Override
		public String toString() {
			return _childs.toString();
		}
	}

	private static class Graph<T> {
		private Map<T, Adjacency<T>> _adjacency;

		public void add(T t) {
			if (!contains(t)) {
				_adjacency.put(t, new Adjacency<T>());
			}
		}

		public void remove(T t) {
			if (_adjacency.containsKey(t)) {
				for (T parent : _adjacency.get(t).getParents()) {
					_adjacency.get(parent).getChilds().remove(t);
				}
				for (T child : _adjacency.get(t).getChilds()) {
					_adjacency.get(child).getParents().remove(t);
				}
				_adjacency.remove(t);
			}
		}

		public boolean isEmpty() {
			return _adjacency.isEmpty();
		}

		public boolean contains(T t) {
			return _adjacency.containsKey(t);
		}

		public boolean hasPath(T t1, T t2) {
			if (_adjacency.containsKey(t1)) {
				Set<T> adj = _adjacency.get(t1).getChilds();
				if (adj.contains(t2)) {
					return true;
				}
				for (T ti : adj) {
					if (hasPath(ti, t2)) {
						return true;
					}
				}
			}
			return false;
		}

		public boolean hasArc(T t1, T t2) {
			if (_adjacency.containsKey(t1)) {
				return _adjacency.get(t1).getChilds().contains(t2);
			}
			return false;
		}

		public Set<T> ascendents(T t) {
			Set<T> asc = new HashSet<T>();
			Set<T> parents = _adjacency.get(t).getParents();
			asc.addAll(parents);
			for (T parent : parents) {
				asc.addAll(ascendents(parent));
			}
			return asc;
		}

		public void addArc(T t1, T t2) {
			add(t1);
			add(t2);
			if (!hasPath(t1, t2)) {
				_adjacency.get(t1).getChilds().add(t2);
				_adjacency.get(t2).getParents().add(t1);
				// trick!
				for (T t0 : ascendents(t1)) {
					if (hasArc(t0, t2)) {
						removeArc(t0, t2);
					}
				}
			}
		}

		public void removeArc(T t1, T t2) {
			if (_adjacency.containsKey(t1)) {
				_adjacency.get(t1).getChilds().remove(t2);
				_adjacency.get(t2).getParents().remove(t1);
			}
		}

		public Set<T> getRoots() {
			Set<T> roots = new HashSet<T>();
			for (Entry<T, Adjacency<T>> e : _adjacency.entrySet()) {
				if (e.getValue().getParents().isEmpty()) {
					roots.add(e.getKey());
				}
			}
			return roots;
		}

		public Set<List<T>> getPermutations() {
			Set<List<T>> paths = new HashSet<List<T>>();
			Set<T> roots = getRoots();
			for (T root : roots) {
				Graph<T> subgraph = clone();
				subgraph.remove(root);
				if (subgraph.isEmpty()) {
					List<T> path = new LinkedList<T>();
					path.add(root);
					paths.add(path);
				} else {
					Set<List<T>> subpaths = subgraph.getPermutations();
					for (List<T> path : subpaths) {
						path.add(0, root);
					}
					paths.addAll(subpaths);
				}

			}
			return paths;
		}

		public Graph() {
			_adjacency = new HashMap<T, Adjacency<T>>();
		}

		public Graph<T> clone() {
			Graph<T> graph = new Graph<T>();
			for (Entry<T, Adjacency<T>> e : _adjacency.entrySet()) {
				graph._adjacency.put(e.getKey(), e.getValue().clone());
			}
			return graph;
		}

		/*
		public void print() {
			for (Entry<T, Adjacency<T>> e : _adjacency.entrySet()) {
				System.out.println(e.getKey() + " -> "
						+ e.getValue().getChilds());
			}
		}
		*/
	}

	private static class Password extends Graph<Character> {

		public void addSubcode(String subcode) {
			for (int i = 0; i < subcode.length() - 1; i++) {
				addArc(subcode.charAt(i), subcode.charAt(i + 1));
			}
		}

		public String[] getWords() {
			SortedSet<String> words = new TreeSet<String>();
			for (List<Character> path : getPermutations()) {
				StringBuilder sb = new StringBuilder();
				for (Character c : path) {
					sb.append(c);
				}
				words.add(sb.toString());
			}
			return words.toArray(new String[] {});
		}

		public Password() {

		}
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		Password password = new Password();

		while (sc.hasNextLine()) {
			password.addSubcode(sc.nextLine());
		}

		for (String word : password.getWords()) {
			System.out.println(word);
		}
	}
}
