#include<bits/stdc++.h>
#include<mpi.h>

using namespace std;

// change 4096 to larger size if you are using larger size inputs
int dist[4096][4096];
int n;
int a,b,c,i,j,k;
int p,my_rank;

int main(int argc, char** argv)
{
    // Initialise communication, get rank and number of processes
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);

    //problem size(please be sure that input of size is available in testcase folder)
    int size = 1024;

    int testcase_no = 0;
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

    int intinf = 1e4;

    string nam;
    string nam1;
        
    nam += s;
    nam += "/input";
    nam += (char)(testcase_no/10 + '0');
    nam += (char)(testcase_no%10 + '0');
    nam += t;

    nam1 += s;
    nam1 += "/output";
    nam1 += (char)(testcase_no/10 + '0');
    nam1 += (char)(testcase_no%10 + '0');
    nam1 += t;

    fstream fin,fout;
    fin.open(nam);
    fout.open(nam1);

    fin >> n;
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            fin >> dist[i][j];

    auto start = MPI_Wtime();
    for(k = 0;k<n;k++)
    {
        a = (n/p) * (my_rank);
        b = (n/p) *(my_rank + 1);
        if(p == n-1)
            b = n;

        MPI_Barrier(MPI_COMM_WORLD);
        // broadcast dist[k] i.e. kth row of matrix to every process and as k/(n/p) has updated kth row it is set as root
        MPI_Bcast(dist[k],n,MPI_INT,k/(n/p),MPI_COMM_WORLD);

        for(i = a;i<b;i++)
            for(j = 0;j<n;j++)
                dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);

        // unless every process computed this iteration don't let any process move forward (as outer loop can't be parallelised in FW algorithm)
        MPI_Barrier(MPI_COMM_WORLD);
    }
    auto end = MPI_Wtime();
    double duration = end - start;

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            fout >> x;
            if(dist[i][j] != x && my_rank == i/(n/p))
            {
                cout << "FAILED " << duration*1000 <<" ms"<< '\n';
                return 0;
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_rank == 0)
        cout << "PASSED and Duration : " << duration*1000 <<"ms" << '\n';
    fin.close();

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}