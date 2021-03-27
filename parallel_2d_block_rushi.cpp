#include<bits/stdc++.h>

using namespace std;

int main()
{
    //statics
    static int BLOCK_SIZE = 4;

    //variables
    int n,k,j,i,a,b,c,x;
    int B;
    vector<vector<int>> dist;

    //input
    fstream fin,fout;
    string name = "./testcase/input/input00.txt";
    fin.open(name);
    fin >> n;
    B = n/BLOCK_SIZE;

    dist.resize(n,vector<int> (n));
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            fin >> dist[i][j];


    for(k = 0;k<n;k+=BLOCK_SIZE)
    {
        //do floyd of row [k to k + B - 1] and col [k to k + B - 1]
        for(a = k;a<=k + BLOCK_SIZE - 1;a++)
            for(b = k;b<=k + BLOCK_SIZE - 1;b++)
                for(c = k;c <= k + BLOCK_SIZE - 1;c++)
                    dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);

        #pragma omp parallel for num_threads(6)
        for(j = 0;j < n;j+=BLOCK_SIZE)
        {
            if(j == k)
                continue;
            //do floyd of row [k to k + B - 1] and col [j to j + B - 1]
            for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                for(b = k;b<=k + BLOCK_SIZE - 1;b++)
                    for(c = j;c <= j + BLOCK_SIZE - 1;c++)
                        dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
        }

        #pragma omp parallel for num_threads(6)
        for(i = 0;i<n;i+=BLOCK_SIZE)
        {
            if(i == k)
                continue;
            //do floyd of row [i to i + B - 1] and col [k to k + B - 1]
            for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                for(b = i;b<=i + BLOCK_SIZE - 1;b++)
                    for(c = k;c <= k + BLOCK_SIZE - 1;c++)
                        dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);

            for(j = 0;j<n;j+=BLOCK_SIZE)
            {
                if(j == k)
                    continue;
                //do floyd of row [i to i + B - 1] and col [j to j + B - 1]
                for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                    for(b = i;b<=i + BLOCK_SIZE - 1;b++)
                        for(c = j;c <= j + BLOCK_SIZE - 1;c++)
                            dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
            }
        }
    }

    //validation
    name = "./testcase/output/output00.txt";
    fout.open(name);
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<n;j++)
        {
            fout >> x;
            if(x != dist[i][j])
            {
                cout << i << " " << j << endl;
                cout << x << " " << dist[i][j] << endl;
                cout << "FAILED\n";
                return 0;
            }
        }
    }
    cout << "PASSED\n";

    fout.close();
    fin.close();

    return 0;
}