#include <iostream>
#include "AStar.h"
using namespace std;


void main()
{
	Tiles tStartState = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 0, 13, 14, 12, 11 };
	
	// Configuration, BlankSpace, Father
	Node *nStartNode = new Node(tStartState, 11, NULL);
	
	nStartNode->iG = 0;

	AStar puzzle15(nStartNode);
	puzzle15.Run();
	/* stampa configurazione */

	getchar();
}