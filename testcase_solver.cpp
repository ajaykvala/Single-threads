#include<bits/stdc++.h>

using namespace std;

int main()
{
    string s = "./testcase/input/input";
    string s1 = "./testcase/output/output";
    string t = ".txt";
    int ss = 0;             // starting number of testcase
    int tt = 40;            // ending number of testcase

    for(int i1 = ss;i1<tt;i1++)
    {
        string nam;
        string nam1;
        nam1 += s1;
        nam += s;
        nam += (char)(i1/10 + '0');
        nam += (char)(i1%10 + '0');
        nam1 += (char)(i1/10 + '0');
        nam1 += (char)(i1%10 + '0');
        nam += t;
        nam1 += t;

        fstream fin,fout;
        fin.open(nam);
        fout.open(nam1,fstream::out);

        int n;
        fin >> n;

        vector<vector<int>> dist(n,vector<int>(n,0));
        for(int i = 0;i<n;i++)
            for(int j = 0;j<n;j++)
                fin >> dist[i][j];

        for(int k = 0;k<n;k++)
        {
            for(int i = 0;i < n;i++)
            {
                for(int j = 0;j < n;j++)
                {
                    dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
                }
            }
        }

        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<n;j++)
                fout << dist[i][j] << " ";
            fout << '\n';
        }

        fin.close();
        fout.close();
    } 


    return 0;
}