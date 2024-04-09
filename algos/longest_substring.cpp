#include <iostream>
#include <unordered_set>

std::string longestSubstringNonRepeatingChars(const std::string& str) {
	int n = str.length();
	int left = 0, right = 0;
	int maxLength = 0;
	std::unordered_set<char> uniqueChars;
	std::string result;

	while (right < n) {
		char currChar = str[right];
		if (!uniqueChars.contains(currChar)) {
			uniqueChars.insert(currChar);
			if (right - left + 1 > maxLength) {
				maxLength = right - left + 1;
				result = str.substr(left, maxLength);
			}
			right++;
		} else {
			uniqueChars.erase(str[left]);
			left++;
		}
	}

	return result;
}

int main() {
	std::string str = "matrijarsija je zakonodavno telo";
	//std::cin >> str;
	std::cout << str << '\n';
	std::cout << longestSubstringNonRepeatingChars(str) << '\n';
	return 0;
}
