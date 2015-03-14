// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "WorldDataInstance.h"
#include "LocationObject.h"
#include "RPGLocation.h"
#include "RPGTown.h"
#include "RPGStructure.h"
#include "RPGDungeon.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, text)

UWorldDataInstance::UWorldDataInstance(const FObjectInitializer& ObjectInitializer) 
	: masterSeed(0)
	, world(nullptr)
	, currentTown(nullptr)
	, currentDungeon(nullptr)
	, Super(ObjectInitializer)
{
}

ULocationObject* UWorldDataInstance::CreateLocation(FName name, FName type, ULocationObject* parent) const
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	print(FString(__FUNCTION__) + " : " + name.ToString() + "/" + type.ToString());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGLocation>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::CreateTown(FName name, FName type, ULocationObject* parent) const
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	print(FString(__FUNCTION__) + " : " + name.ToString() + "/" + type.ToString());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGTown>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::CreateStructure(FName name, FName type, ULocationObject* parent) const
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	print(FString(__FUNCTION__) + " : " + name.ToString() + "/" + type.ToString());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGStructure>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::CreateDungeon(FName name, FName type, ULocationObject* parent) const
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	print(FString(__FUNCTION__) + " : " + name.ToString() + "/" + type.ToString());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGDungeon>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::GetRealmByName(FName name) const
{
	return FindLocationByName(realms, name);
}

ULocationObject* UWorldDataInstance::GetTownByName(FName name) const
{
	return FindLocationByName(towns, name);
}

ULocationObject* UWorldDataInstance::GetDungeonByName(FName name) const
{
	return FindLocationByName(dungeons, name);
}

void UWorldDataInstance::SetCurrentTown(FName name)
{
	currentTown = GetTownByName(name);
}

ULocationObject* UWorldDataInstance::GetCurrentTown() const
{
	return currentTown;
}

void UWorldDataInstance::SetCurrentDungeon(FName name)
{
	currentDungeon = GetDungeonByName(name);
}

ULocationObject* UWorldDataInstance::GetCurrentDungeon() const
{
	return currentDungeon;
}

ULocationObject* UWorldDataInstance::FindLocationByName(TArray<ULocationObject*> locations, const FName& name) const
{
	for (auto location : locations)
	{
		if (location->location->GetName() == name)
			return location;
	}
	return nullptr;
}
