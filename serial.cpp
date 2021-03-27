#include<bits/stdc++.h>

using namespace std;

int main()
{
    //input
    int n,x;
    fstream fin,fout;
    string name = "./testcase/input/input03.txt";
    fin.open(name);
    fin >> n;
    int dist[n][n];
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            fin >> dist[i][j];

    //algo
    auto begin = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

    //validate
    name = "./testcase/output/output03.txt";
    fout.open(name);
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            fout >> x;
            if(x != dist[i][j])
            {
                cout << i << " " << j << endl;
                cout << x << " " << dist[i][j] << endl;
                cout << "FAILED " << duration*1e-6 << "ms" << '\n';
                return 0;
            }
        }
    }
    cout << "PASSED " << duration*1e-6 << "ms" << '\n';

    fout.close();
    fin.close();

    return 0;

}