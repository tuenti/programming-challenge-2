#include <iostream>
#include <string>
#include <cstdlib>

// Not brute force! It runs the most difficult test case (10^6 cards with split in the middle)
// in about 10 minutes in my i5 1.7GHz (using only 1 core). I hope that's enough.
// It could probably be improved with some kind of caching (memoization)
// or precalculation in the gcd (greatest common divisor) function.

// In extreme test cases the unsigned long long is not enough, and it overflows.
// The most practical solution in that case would be using Python (its integers have no limits),
// or some specialized library, but it would be considerably slower.

using namespace std;

// Euclides' method
unsigned long long gcd(unsigned long long a, unsigned long long b) {
	unsigned long long tmp;
	while(b) {
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

long solve(int n_cards, int split) {
	int len_first_deck = split;
	int len_second_deck = n_cards - split;
	
	// unshuffle
	int* cards = (int*) malloc(n_cards*sizeof(int));
	int cursor_first_deck = 0;
	int cursor_second_deck = 0;
	int cards_put = 0;
	while(cards_put < n_cards) {
		if(cursor_first_deck < len_first_deck)
			cards[len_first_deck - 1 - cursor_first_deck++] = cards_put++;
		if(cursor_second_deck < len_second_deck)
			cards[n_cards - 1 - cursor_second_deck++] = cards_put++;
	}
	
	unsigned long long result = 1;
	for(int i=n_cards-1; i>=0; i--) {
		unsigned long long period = 0;
		int cursor = i;
		while(1) {
			cursor = cards[cursor];
			period++;
			if(cursor == i) {
				// lcm(a, b) ====> a * b / gcd(a, b)
				result *= period / gcd(result, period);
				break;
			}
		}
	}
	
	return result;
}

int main() {
	string input_line;
	int n;
	cin >> n;
	getline(cin, input_line); // discard the first line (n)
	for(int i=1; i<=n; i++) {
		int n_cards, split;
		cin >> n_cards >> split;
		cout << "Case #" << i << ": " << solve(n_cards, split) << endl;
	}
	return 0;
}