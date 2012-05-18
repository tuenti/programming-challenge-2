#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string PATH = "documents";
const int NFILES = 800;

string extzeros(int n) {
  stringstream ss;
  ss << setw(4) << setfill('0') << n;
  return ss.str();
}

string tolower(string s) {
  int n = s.size();
  for (int i = 0; i < n; ++i)
    if ('A' <= s[i] and s[i] <= 'Z')
      s[i] = s[i] - 'A' + 'a';
  return s;
}

int main() {
  int input_size;
  cin >> input_size;
  
  vector<pair<string, int> > input(input_size);
  for (int i = 0; i < input_size; ++i) {
    cin >> input[i].first >> input[i].second;
    input[i].first = tolower(input[i].first);
  }
  
  map<string, int> seen;                  // seen[w]: times we have seen word w
  map<pair<string, int>, string> answer;  // here we store the answer we are looking for
  
  for (int i = 0; i < input_size; ++i) {
    seen[input[i].first] = 0;
    answer[pair<string, int>(input[i].first, input[i].second)] = "";
  }
  
  int found = 0;
  for (int filenum = 1; found < int(answer.size()) and filenum <= NFILES; ++filenum) {
    cerr << "filenum=" << filenum << endl;
    string filepath = PATH + "/" + extzeros(filenum);
    
    ifstream f(filepath.c_str(), ifstream::in);
    
    int linenum = 0;
    string line;
    while (getline(f, line)) {
      ++linenum;
      stringstream ss(line);
      
      int colnum = 0;
      string word;
      while (ss >> word) {
        ++colnum;
        word = tolower(word);
        
        if (seen.count(word)) {
          int t = ++seen[word];
          if (answer.count(pair<string, int>(word, t))) {
            stringstream tt;
            tt << filenum << "-" << linenum << "-" << colnum;
            answer[pair<string, int>(word, t)] = tt.str();
            ++found;
          }
        }
      }
    }
    
    f.close();
  }
  
  if (found != int(answer.size())) cerr << "SOME QUERIES FAILED" << endl;
  
  for (int i = 0; i < input_size; ++i)
    cout << answer[input[i]] << endl;
}
