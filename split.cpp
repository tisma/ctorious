#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

vector<string> split(const string& s, char delimiter)
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

int main(int argc, char* argv[])
{
	string text;
	getline(cin, text);

	cout << text << endl;

	istringstream iss(text);

	vector<string> v((istream_iterator<string>(iss)), istream_iterator<string>());


	for (auto const& val : v)
	{
		cout << val << " ";
	}

	cout << endl;

	return 0;
}
