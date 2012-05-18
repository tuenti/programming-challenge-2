/*
 * Tuenti Programming Challenge 2
 * Challenge 12: Three Keys One Cup
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;

public class KeysCup {

	private static int[] KEY1 = new int[] { 0xa5, 0x41, 0x71, 0x4a, 0x17, 0x80,
			0x4a, 0xc2, 0x81, 0xe6, 0xdd, 0xda, 0x5b, 0x70, 0x79, 0x52 };

	private static int[] KEY2 = new int[] { 0xed, 0x8c, 0xe1, 0x5d, 0xa9, 0xb7,
			0xb5, 0xe2, 0xee, 0x70, 0x63, 0x4c, 0xc2, 0x35, 0xe3, 0x63 };

	private static int[] KEY3 = new int[] { 0x62, 0xcd, 0x27, 0x59, 0x89, 0xe7,
			0x8e, 0xe5, 0x6a, 0x81, 0xf0, 0x26, 0x5a, 0x87, 0x56, 0x2e };

	private static final int KEY_SIZE = 16;

	private static int[] input = new int[KEY_SIZE];
	private static int[] output = new int[KEY_SIZE];

	public static void parseInput() {
		Scanner sc = new Scanner(System.in);
		String s = sc.next();
		for (int i = 0; i < KEY_SIZE * 2; i += 2) {
			input[i / 2] = ((Character.digit(s.charAt(i), 16) << 4) | Character
					.digit(s.charAt(i + 1), 16));
		}
	}

	private static void computeOutput() {
		for (int i = 0; i < KEY_SIZE; i++) {
			output[i] = ((((KEY1[i] & 0xf0) >> 4) + ((KEY2[i] & 0xf0) >> 4)
					+ ((KEY3[i] & 0xf0) >> 4) + ((input[i] & 0xf0) >> 4) & 0x0f) << 4)
					| (((KEY1[i] & 0x0f) + (KEY2[i] & 0x0f) + (KEY3[i] & 0x0f) + (input[i] & 0x0f)) & 0x0f);
		}
	}

	private static void printOutput() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < KEY_SIZE; i++) {
			sb.append(String.format("%1$02x", output[i]));
		}
		System.out.println(sb.toString());
	}

	public static void main(String[] args) throws Exception {

		parseInput();
		computeOutput();
		printOutput();
	}
}
