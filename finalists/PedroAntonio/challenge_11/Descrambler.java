/*
 * Tuenti Programming Challenge 2
 * Challenge 11: Descrambler
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.io.File;
import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Map.Entry;

public class Descrambler {

	private Map<BigInteger, String> _hashes;

	private static final int[] PRIMES = new int[] { 2, 3, 5, 7, 11, 13, 17, 19,
			23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
			101 };

	private static final int[] POINTS = new int[] { 1, 3, 3, 2, 1, 4, 2, 4, 1,
			8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

	private int getPoints(String s) {
		int p = 0;
		for (int i = 0; i < s.length(); i++) {
			p += POINTS[s.charAt(i) - 'A'];
		}
		return p;
	}

	private String output(String rack, String word) {
		String s = null;
		int max = 0;
		for (int i = 0; i < word.length(); i++) {
			String test = rack + word.charAt(i);
			BigInteger hash = getHash(test);
			for (Entry<BigInteger, String> e : _hashes.entrySet()) {
				if (hash.remainder(e.getKey()).equals(BigInteger.ZERO)) {
					String w = e.getValue();
					int points = getPoints(w);
					if (points == max) {
						if (w.compareTo(s) < 0) {
							s = w;
						}
					} else if (points >= max) {
						max = points;
						s = w;
					}
				}
			}
		}
		return s + " " + max;
	}

	private BigInteger getHash(String s) {
		BigInteger b = BigInteger.ONE;
		for (int i = 0; i < s.length(); i++) {
			b = b.multiply(BigInteger.valueOf(PRIMES[s.charAt(i) - 'A']));
		}
		return b;
	}

	public Descrambler() {
		_hashes = new HashMap<BigInteger, String>();
	}

	public void preloadWordlist() throws Exception {
		Scanner sc = new Scanner(new File("descrambler_wordlist.txt"));
		while (sc.hasNextLine()) {
			String word = sc.nextLine();
			BigInteger hash = getHash(word);
			if (!_hashes.containsKey(hash)) {
				_hashes.put(hash, word);
			} else {
				String word2 = _hashes.get(hash);
				if (word.compareTo(word2) < 0) {
					_hashes.put(hash, word);
				}
			}
		}
		sc.close();
	}

	public static void main(String[] args) throws Exception {

		Descrambler d = new Descrambler();
		d.preloadWordlist();

		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		for (int i = 0; i < n; i++) {
			sc.nextLine();
			String rack = sc.next();
			String word = sc.next();
			System.out.println(d.output(rack, word));
		}
	}
}
