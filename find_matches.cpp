#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <future>
#include <mutex>
#include <functional>

using namespace std;

mutex m;

bool read_file(ifstream& file, deque<string>& words) {
	if (!file) {
		cerr << "Something wrong with opening file!" << endl;
		return false;
	}

	string word;
	while (file >> word) {
		words.push_back(word);
	}

	return true;
}

inline bool match(const string& pattern, string word) {
	if (pattern.size() != word.size()) {
		return false;
	}
	for (size_t i = 0; i < pattern.size(); i++) {
		if (pattern[i] != '.' && pattern[i] != word[i]) {
			return false;
		}
	}
	return true;
}

vector<string> find_matches(const string& pattern, deque<string>& words) {
	vector<string> results;

	while (true) {

		m.lock();

		if (words.size() == 0) {
			m.unlock();
			return results;
		}

		string word = words.front();
		words.pop_front();

		m.unlock();

		if (match(pattern, word)) {
			results.push_back(word);
		}
	}
}

template<class ASYNC>
inline void print_results(ASYNC &f, const string& pattern, int thread_number) {
	vector<string> words = f.get();
	cout << "Found " << words.size() << " matches for " << pattern 
									 << " in thread " << thread_number << endl;
	for (const auto& w : words) {
		cout << w << ' ';
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cerr << "usage: " << argv[0] << " <text_file> <pattern>" << endl;
		return -1;
	}

	ifstream input_file(argv[1]);
	string pattern = argv[2];

	deque<string> words;

	bool rf = read_file(input_file, words);

	for (const auto& w : words) {
		cout << w << endl;
	}

	cout << "--------" << endl;

	if (rf) {
		auto f1 = async(launch::async, find_matches, pattern, ref(words));
		auto f2 = async(launch::async, find_matches, pattern, ref(words));
		auto f3 = async(launch::async, find_matches, pattern, ref(words));

		// vector<string> matches = find_matches(pattern, words);
		print_results(f1, pattern, 1);
		print_results(f2, pattern, 2);
		print_results(f3, pattern, 3);
	}

	return 0;

}