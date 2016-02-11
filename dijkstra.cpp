#include <climits>
#include <iostream>

using namespace std;

const int VERTICES = 9;

int minDistance(int dist[], bool sptSet[])
{
	int  min = INT_MAX, min_index;

	for (int i = 0; i < VERTICES; i++) {
		if (sptSet[i] == false && dist[i] <= min) {
			min = dist[i];
			min_index = i;
		}
	}

	return min_index;
}

void printSolution(int dist[], int n)
{
	cout << "Vertex		Distance form Source" << endl;
	for (int i = 0; i < VERTICES; i++) {
		cout << i << "\t\t\t" << dist[i] << endl;
	}
}

void dijkstra(int graph[][VERTICES], int src)
{
	int dist[VERTICES];
	bool sptSet[VERTICES];

	for (int i = 0; i < VERTICES; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int i = 0; i < VERTICES - 1; i++) {
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int j = 0; j < VERTICES; j++) {
			if (!sptSet[j] && graph[i][j] && 
				dist[i] != INT_MAX && dist[i] + graph[i][j] < dist[j]) {
				dist[j] = dist[i] + graph[i][j];
			}
		}
	}

	printSolution(dist, VERTICES);
}

int main(int argc, char const *argv[])
{

	int graph[VERTICES][VERTICES] = {

		{  0,  4,  0,  0,  0,  0,  0,  8,  0  },

		{  4,  0,  8,  0,  0,  0,  0, 11,  0  },
		
		{  0,  8,  0,  7,  0,  4,  0,  0,  2  },
		
		{  0,  0,  7,  0,  9, 14,  0,  0,  0  },
		
		{  0,  0,  0,  9,  0, 10,  0,  0,  0  },
		
		{  0,  0,  4,  0, 10,  0,  2,  0,  0  },
		
		{  0,  0,  0, 14,  0,  2,  0,  1,  6  },
		
		{  8, 11,  0,  0,  0,  0,  1,  0,  7  },
		
		{  0,  0,  2,  0,  0,  0,  6,  7,  0  },

	};

	dijkstra(graph, 0);
	
	return 0;
}
