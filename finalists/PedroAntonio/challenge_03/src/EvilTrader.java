/*
 * Tuenti Programming Challenge 2
 * Challenge 3: The Evil Trader
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class EvilTrader {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		List<Integer> lsamples = new LinkedList<Integer>();

		while (sc.hasNextLine()) {
			lsamples.add(Integer.parseInt(sc.nextLine()));
		}

		int count = lsamples.size();

		Integer[] samples = lsamples.toArray(new Integer[count]);
		int[] maxs = new int[count];
		int[] imaxs = new int[count];

		maxs[count - 1] = samples[count - 1];
		imaxs[count - 1] = count - 1;
		for (int i = count - 2; i >= 0; i--) {
			if (samples[i] > maxs[i + 1]) {
				maxs[i] = samples[i];
				imaxs[i] = i;
			} else {
				maxs[i] = maxs[i + 1];
				imaxs[i] = imaxs[i + 1];
			}
		}

		int buy = 0;
		int gain = 0;
		for (int i = 0; i < count; i++) {
			int d = maxs[i] - samples[i];
			if (d > gain) {
				gain = d;
				buy = i;
			}
		}
		int sell = imaxs[buy];

		System.out.println((buy * 100) + " " + (sell * 100) + " " + (gain));
	}
}
