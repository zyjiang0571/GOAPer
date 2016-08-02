#pragma once

#include "GOAPAction.h"

class GOAPNode;

/**
 * Data structure for defining 'edges' in the graph, we include a reference to
 * the action that enables the transition to assist in constructing the plan
 */
class GOAPER_API GOAPNeighbour
{
public:
	GOAPNode* Node;
	TSharedPtr<GOAPAction> Action;
	GOAPNeighbour(GOAPNode* aNode, const TSharedPtr<GOAPAction> aAction) : Node(aNode), Action(TSharedPtr<GOAPAction>(aAction)) {};
	GOAPNeighbour() {};
	~GOAPNeighbour() { Node = nullptr; Action = nullptr; };
};
