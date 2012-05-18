/*
 * Tuenti Programming Challenge 2
 * Challenge 4: 20 Fast 20 Furious
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;

public class KartingCircuit {

	private static long liters(long r, long k, long g, long[] gs) {
		long liters = 0;
		int gptr = 0;
		int gend = 0;
		// it is not specified what to do in this case...
		if (gs[0] > k) {
			return 0;
		}
		for (int j = 0; j < r; j++) {
			int ng = 0;
			do {
				ng += gs[gptr];
				gptr += 1;
				if (gptr > g) {
					gptr -= g;
				}
			} while ((ng + gs[gptr]) <= k && gptr != gend);
			liters += ng;
			gend = gptr;
		}
		return liters;
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		long cases = sc.nextLong();
		for (int i = 0; i < cases; i++) {
			sc.nextLine();
			long r = sc.nextLong();
			long k = sc.nextLong();
			long g = sc.nextLong();
			sc.nextLine();
			long[] gs = new long[(int) g];
			for (int j = 0; j < g; j++) {
				gs[j] = sc.nextLong();
			}
			System.out.println(liters(r, k, g, gs));
		}
	}
}
