/*
 * Tuenti Programming Challenge 2
 * Challenge 2: The Binary Granny
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.math.BigInteger;
import java.util.Scanner;

public class BinaryGranny {

	private static int hazelnuts(BigInteger n) {
		int h = 0;
		BigInteger x = BigInteger.ZERO, y = BigInteger.ZERO;

		while ((y = x.shiftLeft(1).add(BigInteger.ONE)).compareTo(n) < 0) {
			x = y;
			h++;
		}
		y = n.subtract(x);
		while (y.compareTo(BigInteger.ZERO) > 0) {
			if (y.testBit(0)) {
				h++;
			}
			y = y.shiftRight(1);
		}
		return h;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int cases = sc.nextInt();

		for (int i = 0; i < cases; i++) {
			sc.nextLine();
			BigInteger n = sc.nextBigInteger();
			System.out.println("Case #" + (i + 1) + ": " + hazelnuts(n));
		}
	}
}
