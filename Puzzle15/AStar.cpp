#include "AStar.h"
#include <iostream>
#include <windows.h> // To use Sleep()
#include <math.h> // To use abs()

AStar::AStar(Node *startNode)
{
	nStarNode = startNode;
}

void AStar::Run()
{
	ComputeHeuristic(nStarNode);
	if (nStarNode->iG == 0)
	{
		// Lo stato iniziale corrisponde allo stato finale
		PrintPath(nStarNode);
		delete nStarNode;
		return;
	}
	Node *nextNode = CreateNodeAdj(nStarNode);	// Crea le adiacenze e computa le euristiche di ogni singolo nodo e le aggiunge
												// in ordine nella openlist, mettendo il closed il nodo passato, restituisce il nuovo
												// nodo con F migliore
	while (!qOpenList.empty())	// se il nuovo nodo ha euristica 0 sono arrivato alla soluzione
								// elimino i nodi in openlist ed esce dal ciclo
	{
		nextNode = CreateNodeAdj(nextNode); 
	}
}

void AStar::ComputeHeuristic(Node *newNode) const
{
	int iH = 0;
	for (int i = 0; i < 16; ++i)
	{
		int iValue = newNode->tConfiguration.iTiles[i];
		iValue = iValue == 0 ? 15 : iValue - 1;
		// abs(xEnd - xStart) + abs(yEnd - yStart)
		iH += abs((iValue % 4) - (i % 4)) + abs((iValue / 4) - (i / 4));
	}
	newNode->iH = iH;
	// Valutare se calcolare anche iG qui
}

void AStar::PrintPath(Node *finalNode) const
{
	std::list<Node*> qPath;
	while (finalNode != NULL)
	{
		qPath.push_front(finalNode);
		finalNode = finalNode->nFather;
	}
	int rows = 4;
	int cols = 4;
	std::list<Node*>::iterator iEnd(qPath.end());
	for (std::list<Node*>::iterator iter = qPath.begin(); iter != iEnd; ++iter)
	{
		Node *tmp = qPath.front();
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				std::cout << tmp->tConfiguration.iTiles[i*cols + j] << "\t";
			}
			std::cout << std::endl << std::endl;
		}
		Sleep(500);
	}
}

void AStar::Clear()
{
	// Elimino i nodi della ClosedList
	std::list<Node*>::iterator iEnd(qClosedList.end());
	for (std::list<Node*>::iterator iter = qClosedList.begin(); iter != iEnd; ++iter)
	{
		Node *tmp = qClosedList.back();
		delete tmp;
		qClosedList.pop_back();
	}

	// Elimino i nodi della OpenList
	iEnd = qOpenList.end();
	for (std::list<Node*>::iterator iter = qOpenList.begin(); iter != iEnd; ++iter)
	{
		Node *tmp = qOpenList.back();
		delete tmp;
		qOpenList.pop_back();
	}
}