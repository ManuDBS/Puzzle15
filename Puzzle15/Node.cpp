#include "Node.h"

Node::Node(Tiles &newConfiguration)
	: tConfiguration(newConfiguration) 
{};

bool Node::operator==(const Node &other)
{
	for (int i = 0; i < 16; ++i)
	{
		if (tConfiguration.iTiles[i] != other.tConfiguration.iTiles[i])
			return false;
	}
	return true;
}

int Node::getF() const
{
	return iH + iG;
}
