#include <iostream>
#include "AStar.h"
using namespace std;


void main()
{
	Tiles tStartState = { 1, 2, 3, 4, 5, 6, 8, 11, 9, 10, 7, 0, 13, 14, 15, 12 };
	
	// Configuration, BlankSpace, Father
	Node *nStartNode = new Node(tStartState, 11, NULL);
	
	nStartNode->iG = 0;

	AStar puzzle15(nStartNode);
	puzzle15.Run();
	/* stampa configurazione */

	getchar();
}