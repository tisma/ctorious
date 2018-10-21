#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <cctype>

using namespace std;

vector<string> split(string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter))
	{
		tokens.emplace_back(token);
	}

	return tokens;
}

void print_vector(vector<string>& v)
{
	for (auto& val : v)
	{
		cout << val << " ";
		for (auto& c : val)
		{
			c = toupper(c);
			cout << c;
		}
		cout << endl;
	}

	cout << endl;
}

int main(int argc, char* argv[])
{
	string text;
	getline(cin, text);

	// cout << text << endl;

	istringstream iss(text);

	// vector<string> v((istream_iterator<string>(iss)), istream_iterator<string>());

	auto vec = split(text, ' ');

	// print_vector(v);
	print_vector(vec);

	return 0;
}
