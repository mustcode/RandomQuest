// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "LocationObject.h"
#include "RPGLocation.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, text)

ULocationObject::ULocationObject() : location(nullptr)
{
}

ULocationObject::~ULocationObject()
{
	if (location)
		delete location;
}

FName ULocationObject::GetName() const
{
	ensure(location);
	return location->GetName();
}

FName ULocationObject::GetType() const
{
	ensure(location);
	return location->GetType();
}

int32 ULocationObject::GetChildrenCount() const
{
	ensure(location);
	return location->GetChildrenCount();
}

FName ULocationObject::GetChildName(int32 index) const
{
	ensure(location);
	return location->GetChild(index)->GetName();
}

bool ULocationObject::HasChild(FName name) const
{
	ensure(location);
	return location->HasChild(name);
}

void ULocationObject::AddGate(FName name)
{
	ensure(location);
	print(FString(__FUNCTION__) + " : " + name.ToString());
	location->AddGate(name);
}

bool ULocationObject::HasGate(FName name) const
{
	ensure(location);
	return location->HasGate(name);
}

void ULocationObject::AddConnection(FName gateName, ULocationObject* connectTo, FName entrance)
{
	ensure(location);
	ensure(connectTo);
	print(FString(__FUNCTION__) + " : " + gateName.ToString() + " to " + connectTo->GetName().ToString() + "/" + entrance.ToString());
	location->AddConnection(gateName, connectTo->location, entrance);
}
