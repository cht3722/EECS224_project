/*
 * Nqueen_serial.cpp
 *
 *  Created on: 2018年2月22日
 *      Author: haotianchen
 */
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <omp.h>
#include <cstring>
#include <cstdlib>
using namespace std;

bool isValid(vector<string> &nQueens, int row, int col, int &n)
{
	//check if the column had a queen before.
	for (int i = 0; i != row; ++i)
		if (nQueens[i][col] == 'Q')
			return false;
	//check if the 45° diagonal had a queen before.
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
		if (nQueens[i][j] == 'Q')
			return false;
	//check if the 135° diagonal had a queen before.
	for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
		if (nQueens[i][j] == 'Q')
			return false;
	return true;
}

void find_nqueen(int* a, vector<string> &nQueens, int row, int &n)
{
	if (row == n) {
		*a = *a + 1;
		return;
	}
	for (int col = 0; col != n; ++col) {
		if (isValid(nQueens, row, col, n)) {
			nQueens[row][col] = 'Q';
			find_nqueen(a, nQueens, row + 1, n);
			nQueens[row][col] = '.';
		}
	}
}

int nqueens_serial(int n)
{
	int res = 0;
	int* a;
	a = &res;
	vector<string> nQueens(n, string(n, '.'));
	find_nqueen(a, nQueens, 0, n);
	return res;
}
int main (int argc, char* argv[]) {
	int n = -1;
	if (argc == 2) {
	    n = atoi (argv[1]);
	}
	int res = nqueens_serial(n);
	cout << res << endl;
	return 0;
}
