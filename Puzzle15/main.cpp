#include "AStar.h"

void main()
{
	Tiles tStartState = { 2, 0, 4, 8, 1, 7, 10, 3, 5, 9, 6, 12, 13, 14, 11, 15 };
	
	// Configuration, BlankSpace, Father
	Node *nStartNode = new Node(tStartState, 1, NULL);
	
	AStar puzzle15(nStartNode);
	
	puzzle15.Run();

	getchar();
}