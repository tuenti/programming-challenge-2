/*
 * Tuenti Programming Challenge 2
 * Challenge 17: The Solomonic pizza cut
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

public class Pizza {

	private static class Vertex {
		double _x, _y;

		public Vertex(double x, double y) {
			_x = x;
			_y = y;
		}
	}

	private static class Polygon {
		private Set<Vertex> _vertex;
		private Vertex _center;

		public Polygon(Set<Vertex> vertex, Vertex center) {
			_vertex = vertex;
			_center = center;
		}
	}

	public static class Interval implements Comparable<Interval> {
		double _start, _end;

		public Interval(double start, double end) {
			_start = start;
			_end = end;
		}

		public boolean contains(double d) {
			return d > _start && d < _end;
		}

		@Override
		public int compareTo(Interval i) {
			if (_start < i._start) {
				return -1;
			} else if (_start == i._start) {
				if (_end < i._end) {
					return -1;
				} else if (_end > i._end) {
					return 1;
				} else {
					return 0;
				}
			} else {
				return 1;
			}
		}

		@Override
		public String toString() {
			return "(" + _start + "," + _end + ")";
		}
	}

	private static class Intervals {

		private SortedSet<Interval> _intervals;

		public Intervals() {
			_intervals = new TreeSet<Interval>();
		}

		public void add(double start, double end) {
			_intervals.add(new Interval(start, end));
		}

		public Set<Double> endpoints() {
			Set<Double> set = new HashSet<Double>();
			for (Interval i : _intervals) {
				set.add(i._start);
				set.add(i._end);
			}
			return set;
		}

		public boolean contains(double d) {
			for (Interval i : _intervals) {
				if (i.contains(d)) {
					return true;
				}
			}
			return false;
		}
	}

	public void addIngredient(String name, double cx, double cy, double vx,
			double vy, int n) {
		Set<Vertex> vs = new HashSet<Vertex>();
		double phi = Math.atan2(vy - cy, vx - cx);
		double r = Math.sqrt(Math.pow(vx - cx, 2) + Math.pow(vy - cy, 2));
		for (int i = 0; i < n; i++) {
			double theta = ((double) i / n) * (2 * Math.PI) + phi;
			vs.add(new Vertex(cx + r * Math.cos(theta), cy + r
					* Math.sin(theta)));
		}
		Set<Polygon> set = getSet(name);
		set.add(new Polygon(vs, new Vertex(cx, cy)));
	}

	private Set<Polygon> getSet(String name) {
		if (_ingredients.containsKey(name)) {
			return _ingredients.get(name);
		} else {
			Set<Polygon> set = new HashSet<Polygon>();
			_ingredients.put(name, set);
			return set;
		}
	}

	private Map<String, Set<Polygon>> _ingredients;

	public Pizza() {
		_ingredients = new HashMap<String, Set<Polygon>>();
	}

	private double max(List<Double> ds) {
		double max = -100;
		for (Double d : ds) {
			if (d > max) {
				max = d;
			}
		}
		return max;
	}

	private double min(List<Double> ds) {
		double min = 100;
		for (Double d : ds) {
			if (d < min) {
				min = d;
			}
		}
		return min;
	}

	private List<Double> fix(List<Double> ds) {
		List<Double> ds2 = new LinkedList<Double>();
		for (Double d : ds) {
			if (d < 0) {
				ds2.add(d + 2 * Math.PI);
			} else {
				ds2.add(d);
			}
		}
		return ds2;
	}

	public boolean canCut() {
		Intervals intervals = new Intervals();
		for (Set<Polygon> set : _ingredients.values()) {
			for (Polygon ingredient : set) {
				List<Double> as = new LinkedList<Double>();
				for (Vertex v : ingredient._vertex) {
					double phi = Math.atan2(v._y, v._x);
					as.add(phi);
				}
				double start = min(as);
				double end = max(as);
				if (Math.abs(start - end) >= Math.PI) {
					as = fix(as);
					start = min(as);
					end = max(as);
					intervals.add(-Math.PI, end - 2 * Math.PI);
					intervals.add(start, Math.PI);
				} else {
					intervals.add(start, end);
				}
			}
		}

		for (Double theta : intervals.endpoints()) {
			if (!intervals.contains(theta)) {
				double phi = theta + Math.PI;
				if (phi >= Math.PI) {
					phi -= 2 * Math.PI;
				}
				if (!intervals.contains(phi)) {
					if (satisfies(theta - Math.PI / 2)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	private boolean satisfies(double theta) {
		double nx = Math.cos(theta);
		double ny = Math.sin(theta);
		for (Set<Polygon> ps : _ingredients.values()) {
			int sara = 0;
			int daniel = 0;
			for (Polygon p : ps) {
				Vertex c = p._center;
				if (nx * c._x + ny * c._y > 0) {
					sara++;
				} else {
					daniel++;
				}
			}
			if (sara != daniel) {
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int nc = sc.nextInt();
		for (int i = 1; i <= nc; i++) {
			double cx = Double.parseDouble(sc.next());
			double cy = Double.parseDouble(sc.next());
			Double.parseDouble(sc.next()); // radious, is it really needed?
			Pizza pizza = new Pizza();
			int n = sc.nextInt();
			for (int j = 0; j < n; j++) {
				sc.nextLine();
				String name = sc.next();
				int nie = sc.nextInt();
				int ni = sc.nextInt();
				for (int k = 0; k < ni; k++) {
					sc.nextLine();
					double cijx = Double.parseDouble(sc.next());
					double cijy = Double.parseDouble(sc.next());
					double vijx = Double.parseDouble(sc.next());
					double vijy = Double.parseDouble(sc.next());
					pizza.addIngredient(name, cijx - cx, cijy - cy, vijx - cx,
							vijy - cy, nie);
				}
			}
			System.out.println("Case #" + i + ": "
					+ (pizza.canCut() ? "TRUE" : "FALSE"));
		}
	}
}
