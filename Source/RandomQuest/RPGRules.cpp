// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGRules.h"
#include "RPGCharacter.h"

RPGRules::RPGRules()
{
}

RPGRules::~RPGRules()
{
}

void RPGRules::GenerateParty(int numOfMembers)
{
	for (int i = 0; i < numOfMembers; ++i)
	{
		RPGCharacter* character = new RPGCharacter;
		character->Randomize();
		party.Add(character);
	}
}

RPGCharacter* RPGRules::GetCharacter(int index) const
{
	ensure(index >= 0 && index < party.Num());
	return party[index];
}


const TArray<RPGCharacter*>& RPGRules::GetParty() const
{
	return party;
}
