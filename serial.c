#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#define CLK CLOCK_MONOTONIC
// Number of vertices in the graph
#define V 16
#define INF 99999
struct timespec diff(struct timespec start, struct timespec end);
struct timespec diff(struct timespec start, struct timespec end){
	struct timespec temp;
	if((end.tv_nsec-start.tv_nsec)<0){
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	}
	else{
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

int main()
{
	struct timespec start_e2e, end_e2e, start_alg, end_alg, e2e, alg;
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
	int dist[V][V], i, j, k,l;
	for (i = 0; i < V; i++)
			for (j = 0; j < V; j++)
				dist[i][j] = graph[i][j];
	long long int sum = 0;
	for (l=0;l<100;l++)
	{
		clock_gettime(CLK, &start_alg);	/* Start the algo timer */

		/*----------------------Core algorithm starts here----------------------------------------------*/
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
		/*----------------------Core algorithm finished--------------------------------------------------*/

		clock_gettime(CLK, &end_alg);	/* End the algo timer */
		alg = diff(start_alg, end_alg);
		printf("%d,%ld\n",alg.tv_sec, alg.tv_nsec);
		sum += alg.tv_nsec;
	}
	sum = sum/100;
	printf("mean = %d",sum);
 
	return 0;
}
