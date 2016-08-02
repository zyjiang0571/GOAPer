// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GOAPState.h"
#include "GOAPNeighbour.h"
#include "GOAPAtom.h"

/**
 * 
 */
class GOAPER_API GOAPNode
{
public:
	GOAPAtom Atom;
	bool Visited;
	GOAPNeighbour Parent;
	TArray<GOAPNeighbour> Neighbours;

	GOAPNode(EGOAPState aKey, bool aValue) : Atom(GOAPAtom(aKey, aValue)), Visited(false) {};
	~GOAPNode() { Neighbours.Empty(); };
};
