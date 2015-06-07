#include "stdafx.h"

void readFromFile(FILE * f);
void calculateGraph();
void findConnections(int apex, int * components, int size, int counter);
void outputToFile();
int compare(const void *a, const void *b);

int apexs,
edges,
counter,
totalDistance;

struct Edge {
	int start;
	int end;
	int distance;
};

Edge * edge, * result;

int _tmain(int argc, _TCHAR* argv[])
{
	system("cls");

	FILE * f = fopen("input.txt", "r");

	if (f != 0)
	{
		readFromFile(f);
		calculateGraph();
		outputToFile();
	}
	else
	{
		cout << "File not found" << endl;
	}

	system("pause");
}

void readFromFile(FILE * f)
{
	fscanf(f, "%d %d", &apexs, &edges);
	edge = new Edge[edges];
	for (int i = 0; i < edges; i++)
	{
		fscanf(f, "%d %d %d", &edge[i].start, &edge[i].end, &edge[i].distance);
	}
}

int compare(const void *a, const void *b)
{
	return ((Edge*)a)->distance - ((Edge*)b)->distance;
}

void calculateGraph()
{
	counter = 0;
	totalDistance = 0;

	result = new Edge[apexs - 1];
	qsort(edge, edges, sizeof(Edge), compare);

	int * components = new int[apexs];

	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < apexs; j++)
		{
			components[j] = -1;
		}

		findConnections(edge[i].start - 1, components, 1, counter);

		if (components[edge[i].start - 1] != components[edge[i].end - 1])
		{
			result[counter] = edge[i];
			totalDistance += edge[i].distance;
			counter++;
		}

		if (counter == apexs - 1)
		{
			break;
		}
	}

	
}

void findConnections(int apex, int * components, int size, int counter)
{
	components[apex] = size;

	for (int i = 0; i < counter; i++)
	{
		if ((components[result[i].start - 1] == -1) && (result[i].end - 1 == apex))
		{
			findConnections(result[i].start - 1, components, size, counter);
		}

		if ((components[result[i].end - 1] == -1) && (result[i].start- 1 == apex))
		{
			findConnections(result[i].end - 1, components, size, counter);
		}

	}
}

void outputToFile()
{
	FILE * f = fopen("output.txt", "w");

	for (int i = 0; i < counter; i++)
	{
		fprintf(f, "%d %d", result[i].start, result[i].end);
		fputc('\n', f);
	}

	fprintf(f, "%d", totalDistance);

	fclose(f);
	
	cout << "Result was outputed into file" << endl;
}