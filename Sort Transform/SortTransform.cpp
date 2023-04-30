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
                P.push_back(j);
                F_temp[j] = '0';
                break;
            }
        }
        for (int j = 0; j < S.size(); j++)
        {
            if (F[i] == L_temp[j]) {
                Q.push_back(j);
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
        T[Q[i]] = j;
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
void cal_L()
{
    for (int i = 0; i < S.size(); i++)
    {
        if (X_1[Y[i]] >= 0)
            T_1[i] = Y[i] + X_1[Y[i]];
        else
            T_1[i] = Y[i];
        H[i] = T_1[i] + X_1[T_1[i]];
        L_1[i] = T_1[i] - H[i] +1;
    }
}
void getCycle()
{
    int length = 0,begin = 0,temp,count=0;
    while (count < S.size())
    {
        for (int i = begin; i < S.size(); i++)
        {
            if (Check[i] == 0) {
                begin = i;
                break;
            }
        }
        temp = begin;
        while (Check[temp] != 1)
        {
            Check[temp] = 1;
            //cout << "111" << L[Q[temp]] <<P[temp]<< endl;
            //cout << "222" << F[P[temp]] << endl;
            //Y[P[temp]] = temp;
            X_0.push_back(L[temp]);
            aa.push_back(L[temp]);
            temp = Q[temp];
            length++;
            count++;
        }
        Cycle.push_back(aa); 
        aa.clear();
        for (int j = length-1; j > 0; j--) 
        {
            X_1.push_back(j);
        }
        X_1.push_back(1-length);
        length = 0;
    }
    cal_L();
}

char cal_C(int i, int d)
{
    //if (i < 0) i += 12;
    //else if (i >= S.size()) i -= 12;
    cout << i << " "; 
    cout << d << " ";
    cout<< ((Y[i] - H[i] + d) % L_1[i]) + H[i] << endl;
    return X_0[((Y[i] - H[i] + d) % L_1[i]) + H[i]];
}
void GetHeights(int i)
{
    int h = 0,j = i;
    //Height[0] = 0;
    for (int m = 0; m < L_1[i]; m++) 
    {
        while (h < 2)
        {
            if (j == 0) { Height[j] = 0; break; }
            if (j == 1 || (cal_C(j, h) != cal_C(j - 1, h))) {
                cout << "got break at j=" << j << " h=" << h <<" " << "cal_C(j, h) = " << cal_C(j, h) <<" " << "cal_C(j - 1, h)= " << cal_C(j - 1, h) << endl;
                break;
            }
            h++;
        }
        Height[j] = h;
        cout <<"j= "<< j<<"Height" << Height[j] << endl;
        if (h > 0){
            h--;
        }
        j = Q[j];
    }
}
void GetHeights1(int i)
{
    int h = 0, j = i;
    //Height[0] = 0;
    for (int m = 0; m < L_1[i]; m++)
    {
        while (h < 2)
        {
            if (j == S.size()-1 || (cal_C(j, h) != cal_C(j + 1, h)))
                break;
            h++;
        }
        if (j < S.size()-1) {
            Height[j + 1] = h;
        }
            
        cout << "Height" << Height[j] << endl;
        if (h > 0)
            h--;
        j = Q[j];
    }
}
void propagate(int i,int v)
{
    int j = i;
    for (int m = 0; m < L_1[i]; m++) {
        if (D_1[j] < 0) {
            D_1[j] = v;
        }
        j = Q[j];
    }
}
bool compare(int i)
{
    bool a = true;
    if (L_1[i] != L_1[i - 1])
        return false;
    else
    {
        return true;
    }
}
void makeD()
{
    for (int i = 1; i < S.size(); i++)
    {
        if (Height[i] < 0 && L_1[i]>(2 / 2))
        {
            GetHeights(i);
            GetHeights1(i);
        }
    }
    for (int i = 0; i < S.size(); i++)
    {
        if (Height[i] > -1)
        {
            if (Height[i] < 2)
                D_1[i] = 1;
            else
                D_1[i] = 0;
        }
    }
    for (int i = 1; i < S.size(); i++)
    {
        if (D_1[i] < 0)
        {
            if (i == 1 || L_1[i] != L_1[i - 1])
            {
                D_1[i] = 1;
            }
            else
            {
                if (compare(i))
                    propagate(i, 0);
                else
                    propagate(i, 1);
            }
        }
    }
}
void restoreS()
{
    int j = L.find(S[S.size() - 1]);
    for (int i = S.size() - 1; i >= 0; i--)
    {
        S_rec[i] = L[j];
        j = T_1[j];
        C_1[j]--;
        j += C_1[j];
    }
}
void getC()
{
    int j = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (D_1[i] == 1)
            j = i;
        T_1[Q[i]] = j;
        C_1[j]++;
    }
}
int main()
{
    S = "mississippi~";
    getRotationMatrix(M, M_sorted);
    module1_getPQ(M_sorted,P,Q);
    //module2_getD();
    //module3_getC();
    //module4_restoreS();
    getCycle();
    makeD();
    getC();
    restoreS();
    for (int i = 0; i < S.size(); i++)
    {
        cout << S_rec[i] ;
    }
    /*for (int i = 0; i < S.size(); i++) {
        cout << M_sorted[i] << " " << P[i] << "   " << Q[i]<<' '<<D[i] << ' ' << C[i] << ' ' << S_rec[i] << endl;;
    }*/
    //cout << Cycle_length[0] << Cycle_length[1] << endl;
    
    /*cout << endl;
    cout << "  M_sorted" << "   " << "P" << "   " << "Q" << "  " << "Height" <<"   X0" <<"   L(i)" <<"    CT" << endl;
    for (int i = 0; i < S.size(); i++) {
        cout << M_sorted[i] << " " << P[i] << "   " << Q[i] <<"   " << Height[i] <<"        " << X_0[i]<<"     " << L_1[i] <<"    " <<CT[i]<<"     " <<Y[i]<< endl;
    }*/
}