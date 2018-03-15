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

int main (int argc, char* argv[]) {
    
    
	int n = -1;
	if (argc == 2) {
	    n = atoi (argv[1]);
	} else {
	    n = atoi (argv[1]);
        int thread_num = atoi(argv[2]);
	    omp_set_num_threads (thread_num);
	}
    int thread = omp_get_max_threads();

    vector<string> nQueens(n, string(n, '.'));
    vector< vector<string> > board;
    board.push_back(nQueens);

    int size = 1;
    int cur = 0;

    while (size < thread) {
        vector< vector<string> > newboard;
        int newsize = 0;
        for (int i = 0; i < size; i++) {
            vector<string> temp = board.at(i);
            for (int j = 0; j < n; ++j) {
                temp[cur][j] = 'Q';
                if (isValid(temp, cur, j, n)) {
                    vector<string> chessboard(temp);
                    newboard.push_back(chessboard);
                    newsize++;
		        }
                temp[cur][j] = '.';
        	}
        }
        cur++;
        size = newsize;
        board = newboard;
    }
    int ans = 0;
    vector<int> sum(thread);
	cout << "size = " << size << endl;
{
#pragma omp parallel for reduction(+:ans) shared(board, sum, size)

    for (int i = 0; i < thread; i++) {
        int tid = omp_get_thread_num();
	
        int res = 0;
        int* a;
        a = &res;
        int idx = i;
        int sum_thread = 0;
        while (idx < size) { 
            find_nqueen(a, board.at(idx), cur, n);
        	sum_thread += res;
            idx += thread;
            res = 0;
        }
        sum[tid] = sum_thread;
        ans += sum_thread;
    }

}
 
	for (int i = 0; i < thread; i++) {
		cout << "Thread" << i << "'s work:" << sum[i] << endl;
	}	
	cout  << ans << endl;

	return 0;

}
