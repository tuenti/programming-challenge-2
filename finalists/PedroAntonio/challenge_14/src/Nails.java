/*
 * Tuenti Programming Challenge 2
 * Challenge 14: Nails
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;

public class Nails {

	private static final int[][] _h = new int[][] {
			new int[] { 1, 0, 1, 0, 1, 0, 1 },
			new int[] { 0, 1, 1, 0, 0, 1, 1 },
			new int[] { 0, 0, 0, 1, 1, 1, 1 } };

	private static int correct(int z) {
		int s = syndrome(z);
		int f = (s == 0) ? 0 : (1 << (s - 1));
		return z ^ f;
	}

	public static int syndrome(int z) {
		int s = 0;
		for (int i = 0; i < _h.length; i++) {
			int c = 0;
			for (int j = 0; j < _h[i].length; j++) {
				c ^= (_h[i][j] & (1 & (z >> j)));
			}
			s |= c << i;
		}
		return s;
	}

	public static int decode(int z) {
		z = correct(z);
		return ((z >> 2) & 1) << 3 | ((z >> 4) & 1) << 2 | ((z >> 5) & 1) << 1
				| ((z >> 6) & 1) << 0;
	}

	private static int decodeWord(String s) {
		int c = 0;
		for (int i = 0; i < 7; i++) {
			if (s.charAt(i) == '1') {
				c = c | (1 << i);
			}
		}
		c = decode(c);
		return c;
	}

	private static boolean isReadable(String s) {
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			if (c < 0x20 || c > 0x7f) {
				return false;
			}
		}
		return true;
	}

	private static String decodeString(String binary) {
		if (binary.length() % 14 != 0) {
			return "Error!";
		} else {
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < binary.length(); i += 14) {
				String s1 = binary.substring(i, i + 7);
				String s2 = binary.substring(i + 7, i + 14);

				sb.append((char) ((decodeWord(s1) << 4) | decodeWord(s2)));
			}
			String msg = sb.toString();
			if (!isReadable(msg)) {
				return "Error!";
			} else {
				return msg;
			}
		}
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		while (sc.hasNextLine()) {
			System.out.println(decodeString(sc.nextLine()));
		}
	}
}
