#pragma once

#include "NodeState.h"
#include "Tiles.h"

struct Node
{
	Tiles tConfiguration;	
	int iBlankSpace;
	int iF;
	int iG;
	int iH;
	Node* nParent;
	NodeState eState;

	Node(Tiles &newConfiguration);
	bool operator==(const Node &other);
	int getF() const;
};