#include <map>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
	
	map<int, string> m;

	m[1] = "one";
	m[2] = "two";
	m[3] = "three";
	m[4] = "four";
	m[5] = "five";

	cout << m[1] << endl;

	for (auto it = m.cbegin(); it != m.cend(); ++it) {
		cout << it->first << "=>" << it->second << endl;
	}

	return 0;
}
