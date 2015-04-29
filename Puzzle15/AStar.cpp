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

Node* AStar::CreateNodeAdj(Node *newNode)
{

}

void AStar::AddToOpenList(Node *newNode)
{
	// Controllo se la configurazione è in closedlist
	std::list<Node*>::iterator iEnd(qClosedList.end());
	for (std::list<Node*>::iterator iter = qClosedList.begin(); iter != iEnd; ++iter)
	{
		if ((**iter) == *newNode)
			return;
	}
	// L'euristica è già stata calcolata
	bool bInserted(false);
	iEnd = qOpenList.end();
	for (std::list<Node*>::iterator iter = qOpenList.begin(); iter != iEnd; ++iter)
	{
		if (newNode->iF < (*iter)->iF)
		{
			qOpenList.insert(iter, newNode);
			bInserted = true;
			break;
		}
	}
	if (!bInserted)
		qOpenList.push_back(newNode);
}

void AStar::AddToClosedList(Node *newNode)
{
	qClosedList.push_back(newNode);
	if ( newNode != nStarNode ) // il nodo iniziale non finisce in openlist
		qOpenList.remove(newNode);
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
	newNode->iG = newNode->nFather != NULL ? newNode->nFather->iG + 1 : 0;
	newNode->iF = newNode->iG + newNode->iH;
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
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				std::cout << (*iter)->tConfiguration.iTiles[i*cols + j] << "\t";
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
		delete *iter;
		qClosedList.pop_front();
	}

	// Elimino i nodi della OpenList
	iEnd = qOpenList.end();
	for (std::list<Node*>::iterator iter = qOpenList.begin(); iter != iEnd; ++iter)
	{
		delete *iter;
		qOpenList.pop_front();
	}
}