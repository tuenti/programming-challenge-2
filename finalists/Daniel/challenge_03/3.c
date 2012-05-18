#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {
	vector<int> vector_data;
	int line;
	int* data;
	int* selling_points;
	int* buying_points;
	int data_len;
	int win = -9999999;
	int min_index;
	int max_index;
	int len_selling_points = 0;
	int len_buying_points = 0;
	int going_up = 0;
	while(cin >> line)
		vector_data.push_back(line);
	data_len = vector_data.size();
	data = &vector_data[0];
	buying_points = (int*) malloc(data_len*sizeof(int));
	selling_points = (int*) malloc(data_len*sizeof(int));
	
	for(int i=1; i<data_len; i++) {
		if(going_up && data[i] < data[i-1]) {
			selling_points[len_selling_points++] = i-1;
			going_up = 0;
		} else if(!going_up && data[i] > data[i-1]) {
			buying_points[len_buying_points++] = i-1;
			going_up = 1;
		}
	}
	if(going_up)
		selling_points[len_selling_points++] = data_len - 1;
	//cout << data_len << " " << len_buying_points << " " << len_selling_points << endl;
	for(int i=len_buying_points-1; i>=0; i--) {
		for(int j=len_selling_points-1; j>=0; j--) {
			if(selling_points[j] < buying_points[i])
				break;
			if(data[selling_points[j]] - data[buying_points[i]] > win) {
				win = data[selling_points[j]] - data[buying_points[i]];
				min_index = buying_points[i];
				max_index = selling_points[j];
			}
		}
	}
	
	cout << min_index * 100 << " " << max_index * 100 << " " << data[max_index]-data[min_index] << endl;
	
	return 0;
}