// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "WorldDataInstance.h"
#include "LocationObject.h"
#include "CharacterObject.h"
#include "RPGLocation.h"
#include "RPGTown.h"
#include "RPGStructure.h"
#include "RPGDungeon.h"
#include "RPGCharacter.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, text)

UWorldDataInstance::UWorldDataInstance(const FObjectInitializer& ObjectInitializer) 
	: masterSeed(0)
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

UCharacterObject* UWorldDataInstance::CreateCharacter()
{
	UCharacterObject* charObj = NewObject<UCharacterObject>();
	charObj->Init();
	rules.InitCharacter(charObj->character);
	return charObj;
}

void UWorldDataInstance::AddCharacterToParty(UCharacterObject* character)
{
	ensure(character);
	party.Add(character);
}

UCharacterObject* UWorldDataInstance::GetCharacterByIndex(int32 index) const
{
	ensure(index >= 0 && index < party.Num());
	return party[index];
}

int32 UWorldDataInstance::GetCharacterIndex(UCharacterObject* character)
{
	for (int i = 0; i < party.Num(); ++i)
	{
		if (character == party[i])
			return i;
	}
	ensure(false);
	return -1;
}

int32 UWorldDataInstance::GetPartySize() const
{
	return party.Num();
}

void UWorldDataInstance::AddConsequence(FName name)
{
	consequences.Add(name, 1);
}

void UWorldDataInstance::RemoveConsequence(FName name)
{
	consequences.Remove(name);
}

bool UWorldDataInstance::HasConsequence(FName name) const
{
	return consequences.Find(name) != nullptr;
}

bool UWorldDataInstance::AbilityTest(FName name, int32 difficulty, int32& result)
{
	RPGCharacter* chosen = nullptr;
	int32 maxScore = 0;
	for (auto character : party)
	{
		int32 score = character->character->GetAttributeValue(name);
		if (score > maxScore)
		{
			chosen = character->character;
			maxScore = score;
		}
	}
	ensure(chosen != nullptr);
	return rules.AbilityTest(chosen, name, difficulty, result);
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
