/*
 * Tuenti Programming Challenge 2
 * Challenge 6: Cross-Stitched fonts
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;

public class CrossStitch {

	private static int countCharacters(String[] words) {
		int len = 0;
		for (String s : words) {
			len += s.length();
		}
		return len;
	}

	private static boolean validFont(int font, int wc, int hc, int ct,
			String[] words, int ap) {

		if (font > hc) {
			return false; // No vertical space to fit the word
		} else if (words[ap].length() * font > wc) {
			return false; // Even the first word does not fit
		} else {
			int wp = 0;

			for (int i = ap; i < words.length; i++) {
				wp += words[i].length() * font;
				if (wp > wc) {
					return validFont(font, wc, hc - font, ct, words, i);
				}
				wp += font;
				if (wp > wc && (i + 1) < words.length) {
					return validFont(font, wc, hc - font, ct, words, i + 1);
				}
			}

			// all the words are now fit
			return true;
		}
	}

	private static int solve(int w, int h, int ct, String text) {
		String[] words = text.split(" ");
		int size = countCharacters(words);
		int font = (int) Math.floor(Math.sqrt(w * h * ct * ct / size));

		int wc = w * ct, hc = h * ct;
		while (!validFont(font, wc, hc, ct, words, 0)) {
			font--;
		}
		
		return (int) Math.ceil(size * font * font / (2.0 * ct));
	}

	public static void main(String[] args) throws Exception {

		Scanner sc = new Scanner(System.in);
		int cases = sc.nextInt();
		sc.nextLine();

		for (int i = 1; i <= cases; i++) {
			int w = sc.nextInt();
			int h = sc.nextInt();
			int ct = sc.nextInt();
			sc.nextLine();
			String text = sc.nextLine();
			System.out.println("Case #" + i + ": " + solve(w, h, ct, text));
		}
	}
}
