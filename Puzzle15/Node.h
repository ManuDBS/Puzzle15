#pragma once

#include "NodeState.h"
#include "Tiles.h"

struct Node
{
	Tiles tConfiguration;	
	int iBlankPosition;
	int iF; // Evito di calcolarla molte volte
	int iG;
	int iH;
	Node* nFather;
	NodeState eState;

	Node(Tiles &newConfiguration, int blankSpace, Node *father);
	bool operator==(const Node &other);
};