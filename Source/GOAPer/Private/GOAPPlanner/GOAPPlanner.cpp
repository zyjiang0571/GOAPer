
#include "GOAPer.h"
#include "GOAPPlanner.h"
#include "GOAPNeighbour.h"
#include "GOAPNode.h"
#include "GOAPAtom.h"
#include "GOAPAction.h"


/**
/*  Form a plan to satisfy the specified target state					
**/
TArray<TSharedPtr<GOAPAction>> GOAPPlanner::Plan(const EGOAPState aState, const bool aValue, TArray<TSharedPtr<GOAPAction>> aActions, TArray<TSharedPtr<GOAPState>> aCurrentState, AGOAPAIController& controller)
{
	TArray<GOAPNode> Nodes;
	TArray<TSharedPtr<GOAPAction>> Plan;

	// Populate a unique list of nodes, first with preconditions
	// TODO: need a faster lookup method than iterating all the time, map of states probably best
	for (TSharedPtr<GOAPAction> action : aActions)
	{
		// First preconditions
		for (TSharedPtr<GOAPAtom> preCondition : action->PreConditions)
		{
			bool isNodeExists = false;
			for (GOAPNode& pc_node : Nodes)
			{
				if (pc_node.Atom.Key == preCondition->Key && pc_node.Atom.Value == preCondition->Value)
				{
					isNodeExists = true;
				}
			}
			if (!isNodeExists)
			{
				Nodes.Push(GOAPNode(preCondition->Key, preCondition->Value));
			}
		}
		// Then with effects
		for (TSharedPtr<GOAPAtom> effect : action->Effects)
		{
			bool isNodeExists = false;
			for (GOAPNode& ef_node : Nodes)
			{
				if (ef_node.Atom.Key == effect->Key && ef_node.Atom.Value == effect->Value)
				{
					isNodeExists = true;
				}
			}
			if (!isNodeExists)
			{
				Nodes.Push(GOAPNode(effect->Key, effect->Value));
			}
		}
	}

	// Now we have the nodes in the graph, we need to find the edges and add neighbours
	// TODO: As before, need to sort a better way to lookup nodes, this works for now though

	for (GOAPNode& node : Nodes)
	{
		for (TSharedPtr<GOAPAction> action : aActions)
		{
			for (TSharedPtr<GOAPAtom> effect : action->Effects)
			{
				// If this action has an Effect that will lead to this node
				//if (effect->Key == node.Key && effect->Value == node.Value)
				if(*effect == node.Atom)
				{
					// Find the precondition nodes for this action
					for (TSharedPtr<GOAPAtom> preCondition : action->PreConditions)
					{
						for (GOAPNode& neighbourNode : Nodes)
						{
							//if (preCondition->Key == neighbourNode.Key && preCondition->Value == neighbourNode.Value)
							if(*preCondition == neighbourNode.Atom)
							{
								// add to neighbours
								node.Neighbours.Emplace(&neighbourNode, action);
							}
						}
					}
				}
			}
		}
	}

	// This is our stack for Depth First Search
	TArray<GOAPNode*> DFSStack;

	// First find the start node
	for (GOAPNode& node : Nodes)
	{
		if (node.Atom.Key == aState && node.Atom.Value == aValue)
		{
			node.Parent = GOAPNeighbour(&node, nullptr);
			DFSStack.Push(&node);
			break;
		}
	}
	// Depth first search until we find a satisfied node
	while (DFSStack.Num() > 0)
	{
		GOAPNode* current = DFSStack.Pop();
		if (!current->Visited)
		{
			current->Visited = true;
			// Check if we've reached a target node
			if ((&controller)->isStateSatisfied(current->Atom.Key, current->Atom.Value))
			{
				// If so, now walk back up through the parents adding actions to the plan
				while (current->Parent.Node != current)
				{
					Plan.Push(current->Parent.Action);
					current = current->Parent.Node;
				}
				break;
			}
		}
		for (GOAPNeighbour& neighbour : current->Neighbours)
		{
			if (!neighbour.Node->Visited)
			{
				neighbour.Node->Parent = GOAPNeighbour(current, neighbour.Action);
				DFSStack.Push(neighbour.Node);
			}
		}
	}

	return Plan;
}
