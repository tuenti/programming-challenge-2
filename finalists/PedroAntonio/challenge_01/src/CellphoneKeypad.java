/*
 * Tuenti Programming Challenge 2
 * Challenge 1: The Cell Phone Keypad
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;

public class CellphoneKeypad {

	private static final int VERTICAL_COST = 300;
	private static final int HORIZONTAL_COST = 200;
	private static final int DIAGONAL_COST = 350;
	private static final int PRESS_COST = 100;
	private static final int WAIT_COST = 500;

	private static class Position {
		private int _x;
		private int _y;
		private int _times;

		public int getx() {
			return _x;
		}

		public int gety() {
			return _y;
		}
		
		public int gettimes() {
			return _times;
		}

		public Position(int x, int y, int times) {
			_x = x;
			_y = y;
			_times = times;
		}
	}

	private static Position[] _charPositions = new Position[] {
		new Position(0, 1, 1), // A
		new Position(0, 1, 2), // B
		new Position(0, 1, 3), // C		
		new Position(0, 2, 1), // D
		new Position(0, 2, 2), // E
		new Position(0, 2, 3), // F
		new Position(1, 0, 1), // G
		new Position(1, 0, 2), // H
		new Position(1, 0, 3), // I
		new Position(1, 1, 1), // J
		new Position(1, 1, 2), // K
		new Position(1, 1, 3), // L
		new Position(1, 2, 1), // M
		new Position(1, 2, 2), // N
		new Position(1, 2, 3), // O
		new Position(2, 0, 1), // P
		new Position(2, 0, 2), // Q
		new Position(2, 0, 3), // R
		new Position(2, 0, 4), // S
		new Position(2, 1, 1), // T
		new Position(2, 1, 2), // U
		new Position(2, 1, 3), // V
		new Position(2, 2, 1), // W
		new Position(2, 2, 2), // X
		new Position(2, 2, 3), // Y
		new Position(2, 2, 4)  // Z
	};
	
	private static Position[] _digitPositions = new Position[] {
		new Position(3, 1, 1), // 0
		new Position(0, 0, 2), // 1
		new Position(0, 1, 4), // 2
		new Position(0, 2, 4), // 3
		new Position(1, 0, 4), // 4
		new Position(1, 1, 4), // 5
		new Position(1, 2, 4), // 6
		new Position(2, 0, 5), // 7
		new Position(2, 1, 4), // 8
		new Position(2, 2, 5), // 9
	};

	private static Position caplockPosition = new Position(3, 2, 1);
	private static Position spacePosition = new Position(0, 0, 1);

	private static int movingCost(Position from, Position to) {
		int v = Math.abs(from.getx() - to.getx());
		int h = Math.abs(from.gety() - to.gety());
		int d = Math.min(v, h);
		v -= d;
		h -= d;
		return v * VERTICAL_COST 
		     + h * HORIZONTAL_COST
		     + d * DIAGONAL_COST
			 + to.gettimes() * PRESS_COST;
	}

	private static int writingCost(String text) {
		Position p = _digitPositions[0]; // zero button
		boolean caplocked = false;
		int cost = 0;

		for (int i = 0; i < text.length(); i++) {
			char c = text.charAt(i);

			Position to;

			if (Character.isDigit(c)) {
				to = _digitPositions[c - '0'];
			} else if (Character.isLetter(c)) {
				if ((Character.isLowerCase(c) && caplocked)	|| Character.isUpperCase(c) && !caplocked) {
					cost += movingCost(p, caplockPosition);
					p = caplockPosition;
					caplocked = !caplocked;
				}
				to = _charPositions[Character.toLowerCase(c) - 'a'];
			} else if (c == ' ') {
				to = spacePosition;
			} else {
				throw new RuntimeException("invalid character");
			}

			if (p.getx() == to.getx() && p.gety() == to.gety()) {
				cost += WAIT_COST;
			}

			cost += movingCost(p, to);
			p = to;
		}

		return cost;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int cases = sc.nextInt();
		sc.nextLine();

		for (int i = 0; i < cases; i++) {
			String text = sc.nextLine();
			System.out.println(writingCost(text));
		}
	}
}
