#include<bits/stdc++.h>

using namespace std;
using namespace chrono;

#define V 16
#define INF 10000000

int dist[V][V],i,j,k,l;
const int RUNS = 100;

int main()
{
    int graph[V][V] = { {0, 5, INF, 10, 0, 5, INF, 10, 0, 5, 1, 10, 0, 5, INF, 10},
							{INF, 0, 3, INF, INF, 0, 3, INF, INF, 0, 3, INF, INF, 0, 3, INF},
							{INF, INF, 0, 1, INF, INF, 0, 1, 7, INF, 0, 1, INF, INF, 0, 1},
							{INF, 23, INF, 0, INF, INF, INF, 0, INF, INF, INF, 0, INF, INF, INF, 0},
				{0, 5, INF, 10, 0, 5, INF, 10, 0, 5, INF, 10, 0, 5, 2, 10},
							{INF, 0, 3, INF, 34, 0, 3, INF, INF, 0, 3, INF, INF, 0, 3, INF},
							{INF, INF, 0, 1, INF, INF, 0, 1, INF, 89, 0, 1, INF, INF, 0, 1},
							{INF, INF, INF, 0, INF, INF, INF, 0, INF, INF, INF, 0, INF, INF, INF, 0},
				{0, 5, 2, 10, 0, 5, INF, 89, 0, 5, INF, 10, 0, 5, INF, 10},
							{INF, 0, 3, INF, INF, 0, 3, INF, INF, 0, 3, INF, INF, 0, 3, INF},
							{INF, INF, 0, 1, INF, INF, 0, 1, INF, INF, 0, 1, INF, INF, 0, 1},
							{INF, INF, INF, 0, INF, 4, INF, 0, INF, INF, INF, 0, INF, INF, INF, 0},
				{0, 5, INF, 10, 0, 5, INF, 10, 0, 5, INF, 10, 0, 5, INF, 10},
							{INF, 0, 3, INF, INF, 0, 3, 8, INF, 0, 3, INF, INF, 0, 3, INF},
							{INF, INF, 0, 1, INF, INF, 0, 1, INF, 7, 0, 1, INF, INF, 0, 1},
							{INF, INF, INF, 0, INF, INF, INF, 0, INF, INF, 5, 0, INF, INF, INF, 0}
						};

    for(int i = 0;i<V;i++)
        for(int j = 0;j<V;j++)
            dist[i][j] = graph[i][j];

    long long int sum = 0;

    auto start = high_resolution_clock::now(); 
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    auto stop = high_resolution_clock::now(); 
    double time_taken = duration_cast<chrono::nanoseconds>(stop - start).count(); 

    cout << time_taken << endl; 

}