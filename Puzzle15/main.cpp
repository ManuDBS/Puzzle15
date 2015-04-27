#include <iostream>
#include "Node.h"
using namespace std;


void main()
{
	Tiles tProva = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	Tiles tProva2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	
	Node *nProva = new Node(tProva);
	Node *nProva2 = new Node(tProva2);

	if (*nProva == *nProva2)
		cout << "OK";

	getchar();
}