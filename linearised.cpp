#include<bits/stdc++.h>
#include<omp.h>

using namespace std;
using namespace chrono;

int dist[2048][2048];
int linearRowWise[2048*2048];       //assign it manually or call malloc
int n,x,i,j,k;

int main()
{
    //input
    fstream fin,fout;
    string name = "./testcase/input/input02.txt";
    fin.open(name);
    fin >> n;
    
    // linearRowWise = (int*)malloc(n*n*sizeof(int));
    // dist = (int**)malloc(n*sizeof(int));
    // for(i = 0;i<n;i++)
    // {
    //     dist[i] = (int*)malloc(n*sizeof(int));
    // }

    // for(i = 0;i<n;i++)
    //     for(j = 0;j<n;j++)
    //         cout << dist[i][j] << '\n';
    // cout << "HI\n";

    for(i = 0;i<n;i++)
    {
        for(j = 0;j<n;j++)
        {
            fin >> dist[i][j];
        }
    }

    for(i = 0;i<n;i++)
        for(j = 0;j<n;j++)
        {
            linearRowWise[i + j*n] = dist[i][j];
        }


    double begin = omp_get_wtime();
    for(k = 0;k<n;k++)
    {
        #pragma omp parallel for num_threads(4) private(i,j)
        for(i = 0;i < n;i++)
        {
            for(j = 0;j<n;j++)
            {
                dist[i][j] = min(dist[i][j],linearRowWise[i + k*n] + dist[k][j]);
            }
        }

        #pragma omp parallel for num_threads(4) private(i,j)
        for(i = 0;i < n;i++)
        {
            for(j = 0;j<n;j++)
            {
                linearRowWise[i + j*n] = dist[i][j];
            }
        }
    }

    double end = omp_get_wtime();
    double duration = end - begin;

    //validation
    name = "./testcase/output/output02.txt";
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
                cout << "FAILED " << duration*1000 << "ms" << '\n';
                return 0;
            }
        }
    }
    cout << "PASSED " << duration*1000 << "ms" << '\n';

    fout.close();
    fin.close();

    return 0;
}