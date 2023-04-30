#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
using namespace std;
string S,S_rec[12];
vector<string> M;
vector<string> M_sorted;
string  L, F;
vector<int> P, Q;
vector<string> CT;
vector<int> D;
vector<int> T(12, 0);
vector<int> C(12, 0);
vector<int> C_1(12, 0);
vector<char> X_0;
vector<int> X_1;
vector<int> Y = { 1,7,9,4,6,3,2,0,11,8,10,5 };
vector<int> Check(12, 0);
vector<vector<char>> Cycle;
vector<char> aa;
vector<int> H(12, 0);
vector<int> T_1(12, 0);
vector<int> L_1(12, 0);
vector<int> Height(12, -1);
vector<int> D_1(12, -1);