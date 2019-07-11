#include <iostream>
#include <cmath>
#include <deque>
#include <vector>

using namespace std;

bool hasDuplicate(const vector<vector<int>>& A, int start_row, int end_row,
				  int start_col, int end_col, int num_elements);

bool isValidSudoku(const vector<vector<int>>& A) {
	// check rows
	for (int i = 0; i < A.size(); i++) {
		if (hasDuplicate(A, i, i + 1, 0, A.size(), A.size())) {
			return false;
		}
	}

	// check columns
	for (int i = 0; i < A.size(); i++) {
		if (hasDuplicate(A, 0, A.size(), i, i + 1, A.size())) {
			return false;
		}
	}

	// check 3x3 sub-matrix
	int region_size = sqrt(A.size());
	for (int i = 0; i < region_size; i++) {
		for (int j = 0; j < region_size; j++) {
			if (hasDuplicate(A, region_size * i, region_size * (i + 1),
							 region_size * j, region_size * (j + 1), A.size())) {
				return false;
			}
		}
	}

	return true;
}

bool hasDuplicate(const vector<vector<int>>& A, int start_row, int end_row,
				  int start_col, int end_col, int num_elements) {
	deque<bool> is_present(num_elements + 1, false);
	for (int i = start_row; i < end_row; i++) {
		for (int j = start_col; i < end_col; j++) {
			if (A[i][j] != 0 && is_present[A[i][j]]) {
				return true;
			}
			is_present[A[i][j]] = true;
		}
	}

	return false;
}

int main(int argc, char** argv) {

	vector<vector<int>> A(9, vector<int>(9));
	// int x;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// cin >> x;
			A[i][j] = j + 1;
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << isValidSudoku(A) << endl;

	return 0;
}