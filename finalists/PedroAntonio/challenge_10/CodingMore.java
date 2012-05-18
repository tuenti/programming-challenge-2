/*
 * Tuenti Programming Challenge 2
 * Challenge 10: Coding m00re and m00re
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.util.Scanner;
import java.util.Stack;
import java.util.StringTokenizer;

public class CodingMore {

	private static int eval(String exp) {
		StringTokenizer st = new StringTokenizer(exp);
		Stack<Integer> stack = new Stack<Integer>();

		while (st.hasMoreTokens()) {
			String token = st.nextToken();
			try {
				int i = Integer.parseInt(token);
				stack.push(i);
			} catch (NumberFormatException nfe) {
				if (token.equals("@")) {
					int b = stack.pop();
					int a = stack.pop();
					stack.push(a + b);
				} else if (token.equals("$")) {
					int b = stack.pop();
					int a = stack.pop();
					stack.push(a - b);
				} else if (token.equals("#")) {
					int b = stack.pop();
					int a = stack.pop();
					stack.push(a * b);
				} else if (token.equals("&")) {
					int b = stack.pop();
					int a = stack.pop();
					stack.push(a / b);
				} else if (token.equals("mirror")) {
					int a = stack.pop();
					stack.push(-a);
				} else if (token.equals("dance")) {
					int b = stack.pop();
					int a = stack.pop();
					stack.push(b);
					stack.push(a);
				} else if (token.equals("conquer")) {
					int b = stack.pop();
					int a = stack.pop();
					stack.push(a % b);
				} else if (token.equals("breadandfish")) {
					stack.push(stack.peek());
				} else if (token.equals("fire")) {
					stack.pop();
				} else if (token.equals(".")) {
					return stack.peek();
				}
			}
		}
		return -1;
	}

	public static void main(String[] args) throws Exception {

		Scanner sc = new Scanner(System.in);

		while (sc.hasNextLine()) {
			System.out.println(eval(sc.nextLine()));
		}
	}
}
