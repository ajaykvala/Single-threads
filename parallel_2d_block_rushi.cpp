#include<bits/stdc++.h>
#include<omp.h>

using namespace std;
using namespace chrono;

int dist[2048][2048];

int main()
{
    //statics
    static int BLOCK_SIZE = 16;

    //variables
    int n,k,j,i,a,b,c,x;
    int B;

    //input
    fstream fin,fout;
    string name = "./testcase/input/input42.txt";
    fin.open(name);
    fin >> n;
    B = n/BLOCK_SIZE;

    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            fin >> dist[i][j];


    double start = omp_get_wtime();
    
    for(k = 0;k<n;k+=BLOCK_SIZE)
    {
        //do floyd of row [k to k + B - 1] and col [k to k + B - 1]
        for(a = k;a<=k + BLOCK_SIZE - 1;a++)
            for(b = k;b<=k + BLOCK_SIZE - 1;b++)
            {
                #pragma omp loop unroll
                #pragma omp simd
                for(c = k;c <= k + BLOCK_SIZE - 1;c++)
                    dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
            }

        #pragma omp parallel for num_threads(4) private(a,b,c,j)
        for(j = 0;j < n;j+=BLOCK_SIZE)
        {
            if(j == k)
                continue;
            //do floyd of row [k to k + B - 1] and col [j to j + B - 1]
            for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                for(b = k;b<=k + BLOCK_SIZE - 1;b++)
                {
                    #pragma omp loop unroll
                    #pragma omp simd
                    for(c = j;c <= j + BLOCK_SIZE - 1;c++)
                        dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
                }
        }

        #pragma omp parallel for num_threads(4) private(a,b,c,i,j)
        for(i = 0;i<n;i+=BLOCK_SIZE)
        {
            if(i == k)
                continue;
            //do floyd of row [i to i + B - 1] and col [k to k + B - 1]
            for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                for(b = i;b<=i + BLOCK_SIZE - 1;b++)
                {
                    #pragma omp loop unroll
                    #pragma omp simd
                    for(c = k;c <= k + BLOCK_SIZE - 1;c++)
                        dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
                }

            for(j = 0;j<n;j+=BLOCK_SIZE)
            {
                if(j == k)
                    continue;
                //do floyd of row [i to i + B - 1] and col [j to j + B - 1]
                for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                    for(b = i;b<=i + BLOCK_SIZE - 1;b++)
                    {
                        #pragma omp loop unroll
                        #pragma omp simd
                        for(c = j;c <= j + BLOCK_SIZE - 1;c++)
                            dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
                    }
            }
        }
    }
    double end = omp_get_wtime();
    double duration = end - start;

    //validation
    name = "./testcase/output/output42.txt";
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
                cout << "FAILED " << duration*1e-6 << "ms" << '\n';
                return 0;
            }
        }
    }
    cout << "PASSED " << duration*1000 << "ms" << '\n';

    fout.close();
    fin.close();

    return 0;
}