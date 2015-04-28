#pragma once

#include "NodeState.h"
#include "Tiles.h"

struct Node
{
	Tiles tConfiguration;	
	int iBlankPosition;
	//int iF;
	int iG;
	int iH;
	Node* nFather;
	NodeState eState;

	Node(Tiles &newConfiguration, int blankSpace, Node *father);
	bool operator==(const Node &other);
	int getF() const;
};