#include <iostream>
#include "AStar.h"
using namespace std;


void main()
{
	Tiles tStartState = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	
	// Configuration, BlankSpace, Father
	Node *nStartNode = new Node(tStartState, 0, NULL);
	
	nStartNode->iG = 0;

	AStar puzzle15(nStartNode);
	//puzzle15.Run();
	/* stampa configurazione */
	puzzle15.ComputeHeuristic(nStartNode);

	getchar();
}