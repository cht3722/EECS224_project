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
int helper(int i, int n) {
	vector<string> nQueens(n, string(n, '.'));
	int res = 0;
        int* a;
	a = &res;
        nQueens[0][i] = 'Q';
	find_nqueen(a, nQueens, 1, n);
	return res;
}
int main (int argc, char* argv[]) {
	int n = -1;
	if (argc == 2) {
	    n = atoi (argv[1]);
	} else if (argc == 3) {
	    n = atoi (argv[1]);
	    int thread_num = atoi(argv[2]);
	  	    omp_set_num_threads (thread_num);
	}	
	int thread = omp_get_max_threads();
	vector<int> sum(thread, 0);

int i = 0;	
int ans = 0;
{
#pragma omp parallel for reduction(+:ans) // shared(sum, n) private (i, res, nQueens, a)
	for (i = 0; i < n; ++i) {
		int tid = omp_get_thread_num();

		vector<string> nQueens(n, string(n, '.'));
		int res = 0;
		int* a;
		a = &res;
		nQueens[0][i] = 'Q';
		find_nqueen(a, nQueens, 1, n);
		ans += res;
		sum[tid] += res;	
        }
}
	for (int i = 0; i < thread; i++) {
		cout << "Thread" << i << "'s work:" << sum[i] << endl;

//		cout << i << sum[i] << endl; 
	}	
	cout << ans << endl;
	return 0;
}
