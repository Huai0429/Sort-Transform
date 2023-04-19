#include "SortTransform.h"
using namespace std;

bool compare(string str1, string str2)
{
    if (str1[0] < str2[0])
        return 1;
    else if (str1[0] == str2[0] && str1[1] < str2[1])
        return 1;
    else 
        return 0;
}
void getRotationMatrix(vector<string>& M, vector<string>& M_sorted) 
{
    for (int i = 0; i < S.size(); i++) 
    {
        M.push_back(S);
        S.push_back(S[0]);
        S.erase(S.begin());
    }
    M_sorted = M;
    sort(M_sorted.begin(), M_sorted.end(), compare);
}
void module1_getPQ(vector<string>& M_sorted, vector<int> &P, vector<int> &Q)
{
    string L_temp,F_temp;
    for (int i = 0; i < S.size(); i++)
    {
        L.push_back(M_sorted[i][S.size() - 1]);
        F.push_back(M_sorted[i][0]);
    }
    L_temp = L; F_temp = F;
    for (int i = 0; i < S.size(); i++)
    {
        for (int j = 0; j < S.size(); j++)
        {
            if (L[i] == F_temp[j]){
                P.push_back(j + 1);
                F_temp[j] = '0';
                break;
            }
        }
        for (int j = 0; j < S.size(); j++)
        {
            if (F[i] == L_temp[j]) {
                Q.push_back(j + 1);
                L_temp[j] = '0';
                break;
            }
        }
    }
}
void module2_getD() 
{
    for (int i = 0; i < S.size(); i++)
        CT.push_back({ M_sorted[i][0] , M_sorted[i][1] });
    D.push_back(1);
    for (int i = 1; i < S.size(); i++)
    {
        D.push_back( CT[i] == CT[i - 1] ? 0 : 1);
    }
}
void module3_getC()
{
    int j = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (D[i] == 1) 
            j = i;
        T[Q[i]-1] = j;
        C[j]++;
    }
}
void module4_restoreS()
{
    int j = L.find(S[S.size()-1]);
    for(int i=S.size()-1;i>=0;i--)
    {
        S_rec[i] = L[j];
        j = T[j];
        C[j]--;
        j += C[j];
    }
}
int main()
{
    S = "mississippi~";
    getRotationMatrix(M, M_sorted);
    module1_getPQ(M_sorted,P,Q);
    module2_getD();
    module3_getC();
    module4_restoreS();
    for (int i = 0; i < S.size(); i++) {
        cout << M_sorted[i] << " " << P[i] << "   " << Q[i]<<' '<<D[i] << ' ' << C[i] << ' ' << S_rec[i] << endl;;
    }

   for (int i = 0; i < S.size(); i++) {
        cout << M_sorted[i]<< endl;;
   }
}