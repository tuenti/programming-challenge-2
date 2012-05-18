/*
 * Tuenti Programming Challenge 2
 * Challenge 18: Sheep Oriented Programming
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;

public class Sop {

	// "Input is the number of straight cuts made through a round
	// chocolate cake and output is the maximum number of cake
	// pieces that can be produced."

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int cases = sc.nextInt();

		for (int i = 1; i <= cases; i++) {
			sc.nextLine();
			long n = sc.nextInt();
			long o = (n * n + n + 2) / 2;
			System.out.println("Case #" + i + ": " + o);
		}
	}
}
