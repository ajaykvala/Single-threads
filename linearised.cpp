#include<bits/stdc++.h>
#include<omp.h>

using namespace std;
using namespace chrono;

int** dist;
int* linearRowWise;

int main()
{
    //statics

    //variables
    int n,x,i,j;

    //input
    fstream fin,fout;
    string name = "./testcase/input/input42.txt";
    fin.open(name);
    fin >> n;
    
    linearRowWise = (int*)malloc(n*n*sizeof(int));
    dist = (int**)malloc(n*sizeof(int));
    for(i = 0;i<n;i++)
        dist[i] = (int*)malloc(n*sizeof(int));
    

    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            fin >> dist[i][j];

    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
        {
            linearRowWise[i + j*n] = dist[i][j];
        }
    auto begin = std::chrono::high_resolution_clock::now();
    for(int k = 0;k<n;k++)
    {
        #pragma omp parallel for num_threads(4) private(i,j)
        for(i = 0;i < n;i++)
        {
            for(j = 0;j<n;j++)
            {
                dist[i][j] = min(dist[i][j],linearRowWise[i + k*n] + dist[i][j]);
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

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

    //validation
    name = "./testcase/output/output42.txt";
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