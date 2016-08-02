#pragma once
#include "GOAPer.h"
#include "GOAPAtom.h"

class AGOAPAIController;
class GOAPAction;



class GOAPState
{
public:
	GOAPState() {};
	GOAPState(EGOAPState eKey, bool bValue) : Atom{GOAPAtom( eKey, bValue) } {};
	virtual bool Evaluate(AGOAPAIController* controller) = 0;
	bool isSatisfied;
	//EGOAPState Key;
	//bool Value;

	GOAPAtom Atom;
};
