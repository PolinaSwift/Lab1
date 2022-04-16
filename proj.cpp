#include <iostream>
#include <vector>

using namespace std;

struct Bi
{
    double per_A;
    double per_B;
};

int n, m;

void Output(const int n, const int m,  Bi** res)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << res[i][j].per_A << ", " << res[i][j].per_B;
            cout << "  ";
        }
        cout << endl;
    }
}

void Pareto(const int n, const int m, Bi** res)
{
    double max = DBL_MIN;
    double** loc_res = new double* [n];
    for (int i = 0; i < n; ++i)
    {
        loc_res[i] = new double[m];
        for (int j = 0; j < m; ++j)
        {
            loc_res[i][j] = res[i][j].per_A + res[i][j].per_B;
            if (loc_res[i][j] > max)
            {
                max = loc_res[i][j];
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (loc_res[i][j] == max)
            {
                cout << "Pareto optimum : " << res[i][j].per_A << ", " << res[i][j].per_B << endl;
                cout << "Strategy of player A : " << i + 1 << endl;
                cout << "Strategy of player B : " << j + 1 << endl;
            }
        }
    }
}

//void Nash(const int n, const int m, Bi** res)
//{
//    
//    double* res_j_perB = new double[n];
//    for (int i = 0; i < n; ++i)//per_B
//    {
//        
//        double max_B = INT_MIN;
//        for (int j = 0; j < m; ++j)
//        {
//            if (res[i][j].per_B > max_B)
//            {
//                max_B = res[i][j].per_B;
//                res_j_perB[i] = j;
//            }
//        }
//    }
//    double* res_i_perA = new double[m];
//    for (int j = 0; j < m; ++j)//per_A
//    {
//        double max_A = INT_MIN;
//        for (int i = 0; i < n; ++i)
//        {
//            if (res[i][j].per_A > max_A)
//            {
//                max_A = res[i][j].per_A;
//                res_i_perA[j] = i;
//            }
//        }
//    }
//    for (int i = 0; i < n; ++i)
//    {
//        for (int j = 0; j < m; ++j)
//        {
//            if ((res_j_perB[i] == j) && (res_i_perA[j] == i))
//            {
//                cout << "Nash's Equilibrium : " << res[i][j].per_A << ", " << res[i][j].per_B << endl;
//                cout << "Strategy of player A : " << i + 1 << endl;
//                cout << "Strategy of player B : " << j + 1 << endl;
//            }
//        }
//    }
//}

void Nash_m(const int n, const int m, Bi** res)
{
    //vector <vector <int>> res_j_perB;
    vector <int>* res_j_perB = new vector <int>[n];
    // double* res_j_perB = new double[n];
    for (int i = 0; i < n; ++i)//per_B
    {
        vector<int> local;
        double max_B = INT_MIN;
        for (int j = 0; j < m; ++j)
        {
            if (res[i][j].per_B > max_B)
            {
                max_B = res[i][j].per_B;
                //res_j_perB[i] = j;
                local.clear();
                local.push_back(j);
            }
            else if (res[i][j].per_B == max_B)
            {
                local.push_back(j);
            }
        }
        res_j_perB[i] = local;
    }
    vector <int>* res_i_perA = new vector <int>[m];
    for (int j = 0; j < m; ++j)//per_A
    {
        vector<int> local;
        double max_A = INT_MIN;
        for (int i = 0; i < n; ++i)
        {
            if (res[i][j].per_A > max_A)
            {
                max_A = res[i][j].per_A;
                //res_i_perA[j] = i;
                local.clear();
                local.push_back(i);
            }
            else if (res[i][j].per_A == max_A)
            {
                local.push_back(i);
            }
        }
        res_i_perA[j] = local;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            for (int v = 0; v < res_j_perB[i].size(); ++v)
            {
                for (int x = 0; x < res_i_perA[j].size(); ++x)
                {
                    if ((res_j_perB[i][v] == j) && (res_i_perA[j][x] == i))
                    {
                        cout << "Nash's Equilibrium : " << res[i][j].per_A << ", " << res[i][j].per_B << endl;
                        cout << "Strategy of player A : " << i + 1 << endl;
                        cout << "Strategy of player B : " << j + 1 << endl;
                    }
                }
            }
        }
    }
}



int main()
{
    cout << "Number of strategis players A: " ;
    cin >> n;
    cout << "Number of strategis players B: " ;
    cin >> m;
    Bi** res = new Bi*[n];
    cout << "" << endl;
    for (int i = 0; i < n; ++i)
    {
        res[i] = new Bi[m];
        for (int j = 0; j < m; ++j)
        {
            cout << "Input weights: "; 
            cin >> res[i][j].per_A >> res[i][j].per_B;
        }
    }

    /*cout << endl;
    Output(n, m, res);*/

    /*cout << endl;
    Nash_m(n, m, res);*/

    cout << endl;
    Pareto(n, m, res);

     

    return 0;
}
