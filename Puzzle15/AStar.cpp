#include "AStar.h"
#include <iostream> // To use cout
#include <algorithm> // To use swap()
#include <windows.h> // To use Sleep()
#include <math.h> // To use abs()

AStar::AStar(Node *startNode)
{
	nStarNode = startNode;
}

void AStar::Run()
{
	ComputeHeuristic(nStarNode);
	// Lo stato iniziale corrisponde allo stato finale
	if (nStarNode->iH == 0)
	{
		PrintPath(nStarNode);
		delete nStarNode;
		return;
	}
	
	Node *nextNode = nStarNode;	
	// La seconda condizione è per farlo entrare nel ciclo la prima volta
	while (!qOpenList.empty() || nextNode->nFather == NULL )
	{
		nextNode = CreateNodeAdj(nextNode); // crea le adiacenze e le aggiunge in openlist
		if (nextNode->iH == 0)
		{
			PrintPath(nextNode);
			Clear();
			return;
		} else
			AddToClosedList(nextNode);
	}
}

Node* AStar::CreateNodeAdj(Node *newNode)
{
	Node *tmp;
	int iBlankPosition = newNode->iBlankPosition;
	if ( iBlankPosition > 3 ) // sposto dal basso verso l'alto
	{ 
		tmp = new Node(newNode->tConfiguration, iBlankPosition - 4, newNode);
		std::swap(tmp->tConfiguration.iTiles[iBlankPosition], tmp->tConfiguration.iTiles[iBlankPosition - 4]);
		ComputeHeuristic(tmp);
		AddToOpenList(tmp);
	}
	if ( iBlankPosition < 12) // sposto dall'alto verso il basso
	{ 
		tmp = new Node(newNode->tConfiguration, iBlankPosition + 4, newNode);
		std::swap(tmp->tConfiguration.iTiles[iBlankPosition], tmp->tConfiguration.iTiles[iBlankPosition + 4]);
		ComputeHeuristic(tmp);
		AddToOpenList(tmp);
	}
	if ( iBlankPosition % 4 > 0 ) // sposto da destra a sinistra
	{ 
		tmp = new Node(newNode->tConfiguration, iBlankPosition - 1, newNode);
		std::swap(tmp->tConfiguration.iTiles[iBlankPosition], tmp->tConfiguration.iTiles[iBlankPosition - 1]);
		ComputeHeuristic(tmp);
		AddToOpenList(tmp);
	}
	if ( iBlankPosition % 4 < 3 ) // sposto da sinistra a destra
	{ 
		tmp = new Node(newNode->tConfiguration, iBlankPosition + 1, newNode);
		std::swap(tmp->tConfiguration.iTiles[iBlankPosition], tmp->tConfiguration.iTiles[iBlankPosition + 1]);
		ComputeHeuristic(tmp);
		AddToOpenList(tmp);
	}
	Node *nextNode = qOpenList.front();
	return nextNode;
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
	if ( newNode->nFather != NULL ) // il nodo iniziale non finisce in openlist
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
		Sleep(1000);
		system("cls");
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