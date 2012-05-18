/*
 * Tuenti Programming Challenge 2
 * Challenge 13: The Crazy Croupier
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class CrazyCroupier {

	private static int[] buildPerm(int[] ns, int l) {
		int[] first = new int[l];
		int[] second = new int[ns.length - l];
		for (int i = 0; i < first.length; i++) {
			first[i] = ns[i];
		}
		for (int i = 0; i < second.length; i++) {
			second[i] = ns[i + l];
		}

		int[] shuffled = new int[ns.length];
		int f = first.length;
		int s = second.length;
		int max = Math.max(f, s);
		for (int i = 0, j = 0; i < max; i++) {
			if (i < f) {
				shuffled[j++] = first[f - i - 1];
			}
			if (i < s) {
				shuffled[j++] = second[s - i - 1];
			}
		}
		return shuffled;
	}

	private static int[] buildList(int n) {
		int[] list = new int[n];
		for (int i = 0; i < n; i++) {
			list[i] = i;
		}
		return list;
	}

	private static long gcd(long a, long b) {
		while (b > 0) {
			long temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}

	private static long lcm(long a, long b) {
		return a * (b / gcd(a, b));
	}

	private static long lcm(List<Integer> l) {
		long result = l.get(0);
		for (int i = 1; i < l.size(); i++)
			result = lcm(result, l.get(i));
		return result;
	}

	private static long cycleLength(int n, int l) {
		int[] l1 = buildList(n);
		int[] l2 = buildPerm(l1, l);
		List<Integer> cycles = new ArrayList<Integer>();
		int i = 0;
		while (i < n) {
			int cycle = 1;
			int head = 0;
			while (i < n && (head = l1[i++]) == -1)
				;
			if (i >= n) {
				break;
			}
			int elem = l2[head];
			while (head != elem) {
				elem = l2[elem];
				l1[elem] = -1;
				cycle++;
			}
			cycles.add(cycle);
		}
		return lcm(cycles);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int nc = sc.nextInt();
		for (int i = 1; i <= nc; i++) {
			sc.nextLine();
			int n = sc.nextInt();
			int l = sc.nextInt();
			System.out.println("Case #" + i + ": " + cycleLength(n, l));
		}
	}
}
