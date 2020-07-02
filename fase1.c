#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int   insere_na_ordem(int, int[], int);
int   mostra(int[], int);

void  fase1();

int main(int argc, char** argv)
{
	fase1();
	return 0;
}

void fase1()
{
	srand(20200630);
	int v[20];
	int total = 0;
	// de 10 a 1
	for (int i = 10; i > 0; i -= 1)
	{
		total = insere_na_ordem(i, v, total);
		mostra(v, total);
	};
	// de 1 a 10
	total = 0;
	for (int i = 1; i <= 10; i += 1)
	{
		total = insere_na_ordem(i, v, total);
		mostra(v, total);
	};
	// random, 1 a 10
	total = 0;
	for (int i = 1; i <= 10; i += 1)
	{
		total = insere_na_ordem((rand() % 100 + 1), v, total);
		mostra(v, total);
	};
	return;
};

int   mostra(int v[], int N)
{
	printf("V[%2d]: ", N);
	for (int i = 0; i < N; i += 1)
		printf("%d ", v[i]);
	printf("\n");
	return 0;
}

int   insere_na_ordem(int N, int V[], int T)
{	// insere N em V[], V com T elementos
	int pos = 0;
	for (pos = T; pos > 0; pos = pos - 1)
	{
		if (V[pos - 1] > N)
			V[pos] = V[pos - 1];
		else break;
	};	// for()
	V[pos] = N; // pos = posicao certa
	return T + 1;
};
// fim