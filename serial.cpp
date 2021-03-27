#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> dist(n,vector<int>(n,0));
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            cin >> dist[i][j];

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
            cout << dist[i][j] << " ";
        cout << '\n';
    }

    return 0;

}