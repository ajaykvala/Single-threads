#include<bits/stdc++.h>

using namespace std;

int dist[4096][4096];
int n;

int main()
{
    int size = 4096;
    int num = 7;
    for(;size <= 4096;size *= 2)
    {
        string s = "./testcase/";
        int x = size;
        string mp;
        while(x > 0)
        {
            mp += (char)(x%10 + '0');
            x = x/10;
        }
        reverse(mp.begin(),mp.end());
        s += mp;
        string t = ".txt";
        for(int yy = 0;yy < num;yy++)
        {
            cout << yy << '\n';
            int intinf = 1e4;

            string nam;
            string nam1;
            
            nam += s;
            nam += "/input";
            nam += (char)(yy/10 + '0');
            nam += (char)(yy%10 + '0');
            nam += t;

            nam1 += s;
            nam1 += "/output";
            nam1 += (char)(yy/10 + '0');
            nam1 += (char)(yy%10 + '0');
            nam1 += t;
        
            fstream fin,fout;
            fin.open(nam);
            fout.open(nam1,fstream::out);

            fin >> n;
            for(int i = 0;i<n;i++)
                for(int j = 0;j<n;j++)
                    fin >> dist[i][j];

            for(int k = 0;k<n;k++)
            {
                #pragma omp parallel for num_threads(4) 
                for(int i = 0;i<n;i++)
                {
                    #pragma omp simd
                    for(int j = 0;j<n;j++)
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
    }

    return 0;
}