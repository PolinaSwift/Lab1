#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

struct Bi
{
    int per_A;
    int per_B;
};

int n, m;

void Output(const int n, const int m,  Bi** res)
{
    cout << endl;
    cout << "Game matrix (players A in rows, player B in columns)" << endl << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf("%3d, %3d ", res[i][j].per_A, res[i][j].per_B);
        }
        cout << endl;
    }
    cout << endl;
}

void Pareto(const int n, const int m, Bi** res)
{
    cout << endl;
    int max = INT_MIN;
    int** loc_res = new int* [n];
    for (int i = 0; i < n; ++i)
    {
        loc_res[i] = new int[m];
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
                cout << "Pareto's optimum : " << res[i][j].per_A << ", " << res[i][j].per_B << endl;
                cout << "Strategy of player A : " << i + 1 << endl;
                cout << "Strategy of player B : " << j + 1 << endl;
            }
        }
    }
    cout << endl;
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
    cout << endl;
    vector <int>* res_j_perB = new vector <int>[n];
    for (int i = 0; i < n; ++i)//per_B
    {
        vector<int> local;
        int max_B = INT_MIN;
        for (int j = 0; j < m; ++j)
        {
            if (res[i][j].per_B > max_B)
            {
                max_B = res[i][j].per_B;
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
        int max_A = INT_MIN;
        for (int i = 0; i < n; ++i)
        {
            if (res[i][j].per_A > max_A)
            {
                max_A = res[i][j].per_A;
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
    cout << endl;
}



int main()
{
    Bi** res = new Bi * [n];
    char Menu;
    do
    {
        cout << "I - Input bimatrix" << endl << "O - Output bimatrix" << endl << "N - Nash's Equilibrium " << endl << "P - Pareto's optimum" << endl << "E - Exit" << endl;
        cout << endl;
        cin >> Menu;
        Menu = toupper(Menu);
        switch(Menu)
        {
            case 'I':
                bool k;
                cout << endl;
                cout << "Input the number of strategies at least 1 :" << endl;
                do {
                    cout << "Number of strategies players A: ";
                    k = scanf_s("%d", &n);
                    if ((!k) || (n < 1))
                    {
                        puts("Invald data");
                        cin.get();
                    }
                } while ((!k) || (n < 1));
                do {
                    cout << "Number of strategies players B: ";
                    k = scanf_s("%d", &m);
                    if ((!k) || (m < 1))
                    {
                        puts("Invald data");
                        cin.get();
                    }
                } while ((!k) || (m < 1));
                cout << endl;
                cout << "Input players' weights" << endl;
                for (int i = 0; i < n; ++i)
                {
                    res[i] = new Bi[m];
                    for (int j = 0; j < m; ++j)
                    {
                        do {
                            cout << "Player A, position: " << i + 1 << " " << j + 1 << endl;
                            k = scanf_s("%d", &res[i][j].per_A);
                            if (!k)
                            {
                                puts("Invald data");
                                cin.get();
                            }
                        } while (!k);
                        do {
                            cout << "Player B, position: " << i + 1 << " " << j + 1 << endl;
                            k = scanf_s("%d", &res[i][j].per_B);
                            if (!k)
                            {
                                puts("Invald data");
                                cin.get();
                            }
                        } while (!k);
                    }
                }
                cout << endl;
                break;
            case 'O':
                Output(n, m, res);
                break;
            case 'N':
                Nash_m(n, m, res);
                break;
            case 'P':
                Pareto(n, m, res);
                break;
            case 'E':
                break;
            default:
                cout << "Unspoken command" << endl;
        }
    } while (Menu != 'E');


    return 0;
}
