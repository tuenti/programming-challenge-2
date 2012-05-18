/*
 * Tuenti Programming Challenge 2
 * Challenge 5: Time is never time again
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;
import java.util.StringTokenizer;

public class TimeAgain {

	static DateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	// New clock
	private static final int[][] newClockDeltas = new int[][] {
		{ 0,  0, -1, -1, -1, -1, -1, -1, -1, -1},
		{ 4,  0,  4, -1, -1, -1, -1, -1, -1, -1},
		{ 2, -1,  0,  1, -1, -1, -1, -1, -1, -1},
		{ 2, -1, -1,  0,  1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1,  0,  2, -1, -1, -1, -1},
		{ 2, -1, -1, -1, -1,  0,  1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1,  0,  1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1,  0,  4, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1,  0,  0},
		{ 1, -1, -1, -1, -1, -1, -1, -1, -1,  0}
	};
	                                               
	private static int getNewClockDeltas(int s) {

		int deltas = 36; // turn on

		int oldHours = 0, oldMinutes = 0, oldSeconds = 0;

		for (int i = 0; i <= s; i++) {
			int hours = (i / 3600) % 24;
			int minutes = (i / 60) % 60;
			int seconds = i % 60;

			if (hours != oldHours) {
				deltas += newClockDeltas[oldHours / 10][hours / 10];
				deltas += newClockDeltas[oldHours % 10][hours % 10];
			}
			if (minutes != oldMinutes) {
				deltas += newClockDeltas[oldMinutes / 10][minutes / 10];
				deltas += newClockDeltas[oldMinutes % 10][minutes % 10];
			}
			if (seconds != oldSeconds) {
				deltas += newClockDeltas[oldSeconds / 10][seconds / 10];
				deltas += newClockDeltas[oldSeconds % 10][seconds % 10];
			}

			oldHours = hours;
			oldMinutes = minutes;
			oldSeconds = seconds;
		}

		return deltas;
	}

	// Old clock.
	private static final int[] oldClockDeltas = new int[] { 6, 2, 5, 5, 4, 5,
			6, 3, 7, 6 };

	private static int getOldClockDeltas(int s) {

		int deltas = 0;
		for (int i = 0; i <= s; i++) {
			int hours = (i / 3600) % 24;
			int minutes = (i / 60) % 60;
			int seconds = i % 60;

			deltas += oldClockDeltas[hours / 10];
			deltas += oldClockDeltas[hours % 10];
			deltas += oldClockDeltas[minutes / 10];
			deltas += oldClockDeltas[minutes % 10];
			deltas += oldClockDeltas[seconds / 10];
			deltas += oldClockDeltas[seconds % 10];
		}
		return deltas;
	}
	
	private static int diff(Date d1, Date d2) {

		long seconds = (d2.getTime() - d1.getTime()) / 1000;

		int newClockDeltas = getNewClockDeltas((int) seconds);
		int oldClockDeltas = getOldClockDeltas((int) seconds);

		return oldClockDeltas - newClockDeltas;
	}

	public static void main(String[] args) throws Exception {

		Scanner sc = new Scanner(System.in);

		while (sc.hasNextLine()) {
			String line = sc.nextLine().replace(" - ", ",");
			StringTokenizer st = new StringTokenizer(line, ",");
			Date d1 = formatter.parse(st.nextToken());
			Date d2 = formatter.parse(st.nextToken());
			System.out.println(diff(d1, d2));
		}
	}
}
