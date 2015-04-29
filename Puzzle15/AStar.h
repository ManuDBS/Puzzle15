#pragma once

#include "Node.h"
#include <list>

class AStar
{
	private:
		Node *nStarNode;
		std::list<Node*> qOpenList;
		std::list<Node*> qClosedList;

		void AddToClosedList(Node *newClosedNode); // Aggiunge i nodi alla ClosedList
		void AddToOpenList(Node *newOpenNode); // Aggiunge, ordinati, i nodi alla OpenList
		Node* CreateNodeAdj(Node *newNode); // Crea le nuove adiacenze partendo da newNode, restituisce il nodo migliore
		void ComputeHeuristic(Node *newNode) const; // Calcola iH per il nodo newNode
		void Clear(); // Pulisce la Openlist e la ClosedList
		void PrintPath(Node *finalNode) const; // Stampa il percorso dato il nodo finale

	public:
		AStar(Node *StartNode);
		void Run(); // Fa partire l'algoritmo
};