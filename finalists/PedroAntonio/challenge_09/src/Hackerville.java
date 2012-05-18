/*
 * Tuenti Programming Challenge 2
 * Challenge 9: Il nomme della magnolia
 * 
 * Author: Pedro Antonio Pardal Jimena
 *         ppardalj@gmail.com
 */

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Formatter;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Hackerville {

	private static class Appearance {
		private int _document, _line, _position;

		public Appearance(int document, int line, int position) {
			_document = document;
			_line = line;
			_position = position;
		}

		@Override
		public String toString() {
			return _document + "-" + _line + "-" + _position;
		}
	}

	private void processLine(int fileid, int lineid, String s) {
		StringTokenizer st = new StringTokenizer(s);
		int position = 1;
		while (st.hasMoreTokens()) {
			String word = st.nextToken();
			if (_indexes.containsKey(word)) {
				List<Integer> list = _indexes.get(word);
				for (int i = 0; i < list.size(); i++){
					int n = list.get(i);
					_cases[n]--;
					if (_cases[n] == 0) {
						_appearances[n] = new Appearance(fileid, lineid, position);
						list.remove(i);
						i--;
					}
				}
				if(list.isEmpty()){
					_indexes.remove(word);
				}
				if (end()) {
					return;
				}
			}
			position++;
		}
	}

	private int[] _cases;
	private Appearance[] _appearances;
	private Map<String, List<Integer>> _indexes;

	public Hackerville(int[] cs, Map<String, List<Integer>> idxs) throws Exception {
		_cases = cs;
		_indexes = idxs;
		_appearances = new Appearance[cs.length];
		find();
	}

	private boolean end() {
		return _indexes.size() == 0;
	}

	private void find() throws Exception {

		for (int i = 1; !end() && i <= 800; i++) {
			String filename = "documents/" + new Formatter().format("%04d", i);
			FileReader file = new FileReader(filename);
			BufferedReader reader = new BufferedReader(file);

			String s;
			int lineid = 1;
			while (!end() && (s = reader.readLine()) != null) {
				processLine(i, lineid, s.toLowerCase());
				lineid++;
			}

			reader.close();
			file.close();
		}
	}

	public static void main(String[] args) throws Exception {

		Scanner sc = new Scanner(System.in);
		int nc = sc.nextInt();
		int[] cs = new int[nc];
		Map<String, List<Integer>> idxs = new HashMap<String, List<Integer>>();
		for (int i = 0; i < nc; i++) {
			sc.nextLine();
			String s = sc.next();
			cs[i] = sc.nextInt();
			List<Integer> set;
			if (idxs.containsKey(s)){
				set = idxs.get(s);
			} else {
				set = new LinkedList<Integer>();
				idxs.put(s, set);
			}
			set.add(i);
		}

		Hackerville h = new Hackerville(cs, idxs);
		for (int i = 0; i < nc; i++) {
			System.out.println(h._appearances[i].toString());
		}
	}
}
