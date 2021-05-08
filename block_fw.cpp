#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int dist[4096][4096];
int n;
int a,b,c,i,j,k;
int arr[6]={1,2,3,4,8,16};
int main()
{
    //set start size of input and end size of input. Please be sure that testcases of set sizes are available in testcase folder.
    int start_size = 128;
    int end_size = 2048;

    string name_csv = "Result_parallel_block_FW.csv";
    fstream csvv;
    csvv.open(name_csv,fstream::out);
    csvv << "Format : Size, Threads, Duration(ms), Speedup, Efficiency\n\n";

    int size = start_size;
    for(;size <= end_size;size *= 2)
    {
        // number of runs (recommended 35 for small problem sizes, and 7 for large problem sizes)
        int num = 7;

        string s = "./testcase/";
        int x = size;
        string mp;
        // Set block size here
        static int BLOCK_SIZE = 32;
        while(x > 0)
        {
            mp += (char)(x%10 + '0');
            x = x/10;
        }
        reverse(mp.begin(),mp.end());
        s += mp;
        string t = ".txt";
        double base_duration;
        double speed_up;

        for(int th = 0;th <= 5;th++)
        {
            int thds=arr[th];
            vector<double> pk;
            for(int yy = 0;yy < num;yy++)
            {
                int yyy = yy%7;
                int intinf = 1e4;

                string nam;
                string nam1;

                nam += s;
                nam += "/input";
                nam += (char)(yyy/10 + '0');
                nam += (char)(yyy%10 + '0');
                nam += t;

                nam1 += s;
                nam1 += "/output";
                nam1 += (char)(yyy/10 + '0');
                nam1 += (char)(yyy%10 + '0');
                nam1 += t;

                fstream fin,fout;
                fin.open(nam);
                fout.open(nam1);

                //Input
                fin >> n;
                for(int i = 0;i<n;i++)
                    for(int j = 0;j<n;j++)
                        fin >> dist[i][j];

                //Core code
                double start = omp_get_wtime();
                for(k = 0;k<n;k+=BLOCK_SIZE)
                {
                    //do FW of row [k to k + B - 1] and col [k to k + B - 1]
                    for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                        for(b = k;b<=k + BLOCK_SIZE - 1;b++)
                        {
                            #pragma omp loop unroll
                            #pragma omp simd
                            for(c = k;c <= k + BLOCK_SIZE - 1;c++)
                                dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
                        }

                    #pragma omp parallel for num_threads(thds) private(a,b,c,j)
                    for(j = 0;j < n;j+=BLOCK_SIZE)
                    {
                        if(j == k)
                            continue;
                        //do FW of row [k to k + B - 1] and col [j to j + B - 1]
                        for(a = k;a<=k + BLOCK_SIZE - 1;a++)
                            for(b = k;b<=k + BLOCK_SIZE - 1;b++)
                            {
                                #pragma omp loop unroll
                                #pragma omp simd
                                for(c = j;c <= j + BLOCK_SIZE - 1;c++)
                                    dist[b][c] = min(dist[b][c],dist[b][a] + dist[a][c]);
                            }
                    }

                    #pragma omp parallel for num_threads(thds) private(a,b,c,i,j)
                    for(i = 0;i<n;i+=BLOCK_SIZE)
                    {
                        if(i == k)
                            continue;
                        //do FW of row [i to i + B - 1] and col [k to k + B - 1]
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
                            //do FW of row [i to i + B - 1] and col [j to j + B - 1]
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
                double duration = (end - start)*1000;
                pk.push_back(duration);

                //validation
                int x;
                for(int i = 0;i<n;i++)
                {
                    for(int j = 0;j<n;j++)
                    {
                        fout >> x;
                        if(dist[i][j] != x)
                        {
                            cout << "FAILED " << duration <<" ms"<< '\n';
                            return 0;
                        }
                    }
                }

                fin.close();
                fout.close();
            }
            if(thds == 1)
            {
                sort(pk.begin(),pk.end());
                base_duration = pk[num/2];
                csvv << size << "," << thds << "," << pk[num/2] << '\n';
            }
            else
            {
                sort(pk.begin(),pk.end());
                speed_up = base_duration/pk[num/2];
                csvv << size << "," << thds << "," << pk[num/2] << "," << speed_up << "," << speed_up/thds << '\n';
            }
        }
        csvv << '\n';
    }

    return 0;
}
