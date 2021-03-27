#include<bits/stdc++.h>

using namespace std;

int main()
{
    //statics
    static int BLOCK_SIZE = 4;
    //variables
    int n,k,j,i,a,b,c;
    int B = n/BLOCK_SIZE;
    vector<vector<int>> dist;
    //input
    fstream fin;
    string name = "input00.txt";
    fin.open(name);
    fin >> n;

    dist.resize(n,vector<int> (n));
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            fin >> dist[i][j];


    for(k = 0;k<n;k+=B)
    {
        //do floyd of row [k to k + B - 1] and col [k to k + B - 1]
        for(a = k;a<=k + B - 1;a++)
            for(b = k;b<=k + B - 1;b++)
                for(c = k;c <= k + B - 1;c++)
                    dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);

        for(j = 0;j < n;j+=B)
        {
            if(j == k)
                continue;
            //do floyd of row [k to k + B - 1] and col [j to j + B - 1]
            for(a = k;a<=k + B - 1;a++)
                for(b = k;b<=k + B - 1;b++)
                    for(c = j;c <= j + B - 1;c++)
                        dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
        }

        for(i = 0;i<n;i+=B)
        {
            if(i == k)
                continue;
            //do floyd of row [i to i + B - 1] and col [k to k + B - 1]
            for(a = k;a<=k + B - 1;a++)
                for(b = i;b<=i + B - 1;b++)
                    for(c = k;c <= k + B - 1;c++)
                        dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);

            for(j = 0;j<n;j+=B)
            {
                if(j == k)
                    continue;
                //do floyd of row [i to i + B - 1] and col [j to j + B - 1]
                for(a = k;a<=k + B - 1;a++)
                    for(b = i;b<=i + B - 1;b++)
                        for(c = j;c <= j + B - 1;c++)
                            dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
            }
        }
    }

    return 0;
}