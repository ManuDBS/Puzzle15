#include "Node.h"

Node::Node(Tiles &newConfiguration, int blankPosition, Node *father)
	:
	tConfiguration(newConfiguration),
	iBlankPosition(blankPosition)
{
	nFather = father;
};

bool Node::operator==(const Node &other)
{
	for (int i = 0; i < 16; ++i)
	{
		if (tConfiguration.iTiles[i] != other.tConfiguration.iTiles[i])
			return false;
	}
	return true;
}
