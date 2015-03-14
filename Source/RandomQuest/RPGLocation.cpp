// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGLocation.h"

RPGLocation::RPGLocation(const FName& locationName, const FName& locationType, RPGLocation* parentLocation)
	: name(locationName)
	, type(locationType)
	, parent(nullptr)
{
	SetParent(parentLocation);
}

RPGLocation::RPGLocation() : parent(nullptr)
{
}

RPGLocation::~RPGLocation()
{
	SetParent(nullptr);
	DetachFromChildren();
}

void RPGLocation::AddChild(RPGLocation* child)
{
	ensure(!HasChild(child->name));
	children.Add(child);
	child->parent = this;
}

void RPGLocation::SetParent(RPGLocation* newParent)
{
	if (parent)
		DetachFromParent();
	parent = newParent;
	if (parent)
		parent->AddChild(this);
}

void RPGLocation::DetachFromParent()
{
	ensure(parent);
	parent->children.Remove(this);
	parent = nullptr;
}

void RPGLocation::DetachFromChildren()
{
	for (auto child : children)
		child->parent = nullptr;
	children.Empty();
}

bool RPGLocation::HasParent() const
{
	return parent != nullptr;
}

bool RPGLocation::HasChild(const FName& name) const
{
	for (auto child : children)
	{
		if (child->name == name)
			return true;
	}
	return false;
}

bool RPGLocation::IsParentOf(RPGLocation* child) const
{
	for (auto location : children)
	{
		if (location == child)
			return true;
	}
	return false;
}

void RPGLocation::AddGate(const FName& name)
{
	ensure(!HasGate(name));
	gates.Add(Gate(name));
}

bool RPGLocation::HasGate(const FName& name) const
{
	for (auto gate : gates)
	{
		if (gate.name == name)
			return true;
	}
	return false;
}

void RPGLocation::AddConnection(const FName& gateName, RPGLocation* connectTo, const FName& entrance)
{
	ensure(connectTo);
	ensure(!HasConnection(gateName, connectTo, entrance));
	for (int i = 0; i < gates.Num(); ++i)
	{
		if (gates[i].name == gateName)
			gates[i].connections.Add(Connection(connectTo, entrance));
	}
}

bool RPGLocation::HasConnection(const FName& gateName, RPGLocation* connectTo, const FName& entrance) const
{
	ensure(connectTo);
	for (auto gate : gates)
	{
		if (gate.name != gateName)
			continue;
		for (auto location : gate.connections)
		{
			if (location.connectTo == connectTo && location.entrance == entrance)
				return true;
		}
	}
	return false;
}

bool RPGLocation::IsConnected(RPGLocation* connectTo) const
{
	ensure(connectTo);
	for (auto gate : gates)
	{
		for (auto location : gate.connections)
		{
			if (location.connectTo == connectTo)
				return true;
		}
	}
	return false;
}

RPGLocation* RPGLocation::GetChild(int32 index) const
{
	ensure(index >= 0 && index < children.Num());
	return children[index];
}

int32 RPGLocation::GetChildrenCount() const
{
	return children.Num();
}
