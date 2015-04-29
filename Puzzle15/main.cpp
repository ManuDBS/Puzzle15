#include <iostream>
#include "AStar.h"
using namespace std;


void main()
{
	Tiles tStartState = { 10, 1, 3, 2, 0, 4, 8, 12, 6, 5, 13, 7, 9, 14, 15, 11 };
	
	// Configuration, BlankSpace, Father
	Node *nStartNode = new Node(tStartState, 4, NULL);
	
	nStartNode->iG = 0;

	AStar puzzle15(nStartNode);
	puzzle15.Run();
	/* stampa configurazione */

	getchar();
}