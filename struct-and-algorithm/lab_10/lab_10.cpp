#include "stdafx.h"

void createEdgeList(FILE * f);
void Kruskal();
void DFS(int apex, int * components, int nComponents, int length);
void outputMST(int weightOfMST, int length);
int compare(const void *a, const void *b);

int nApex,
nEdge;

struct Edge {
	int begin, 
		end, 
		weigth;
} * edge, 
  * MST;

int _tmain(int argc, _TCHAR* argv[])
{
	char key, filename[20];
	do
	{
		system("cls");

		FILE * f = fopen("input.txt", "r");

		if (f != 0)
		{
			createEdgeList(f);
			Kruskal();
		}
		else
		{
			cout << "File not found" << endl;
		}

		cout << "Repeat program y/n?" << endl;
		cin >> key;

	} while (key != 'n');
}

void createEdgeList(FILE * f)
{
	fscanf(f, "%d %d", &nApex, &nEdge);
	edge = new Edge[nEdge];
	for (int i = 0; i < nEdge; i++)
	{
		fscanf(f, "%d %d %d", &edge[i].begin, &edge[i].end, &edge[i].weigth);
	}
}

int compare(const void *a, const void *b)
{
	return ((Edge*)a)->weigth - ((Edge*)b)->weigth;
}

void Kruskal()
{
	MST = new Edge[nApex - 1];
	qsort(edge, nEdge, sizeof(Edge), compare);

	int * components = new int[nApex],
		length = 0,
		weightOfMST = 0;

	for (int i = 0; i < nEdge; i++)
	{
		for (int j = 0; j < nApex; j++)
		{
			components[j] = -1;
		}

		DFS(edge[i].begin - 1, components, 1, length);

		if (components[edge[i].begin - 1] != components[edge[i].end - 1])
		{
			MST[length] = edge[i];
			length++;
			weightOfMST += edge[i].weigth;
		}

		if (length == nApex - 1)
		{
			break;
		}
	}

	outputMST(weightOfMST, length);
}

void DFS(int apex, int * components, int nComponents, int length)
{
	components[apex] = nComponents;

	for (int i = 0; i < length; i++)
	{
		if ((components[MST[i].begin - 1] == -1) && (MST[i].end - 1 == apex))
		{
			DFS(MST[i].begin - 1, components, nComponents, length);
		}

		if ((components[MST[i].end- 1] == -1) && (MST[i].begin- 1 == apex))
		{
			DFS(MST[i].end - 1, components, nComponents, length);
		}

	}
}

void outputMST(int weightOfMST, int length)
{
	cout << "\nMinimal spinning-tree: " << endl << endl;

	for (int i = 0; i < length; i++)
	{
		cout << MST[i].begin << " " << MST[i].end << endl;
	}

	cout << "\nWeigth" << weightOfMST << endl;
}