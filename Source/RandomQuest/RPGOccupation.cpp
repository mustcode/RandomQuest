// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGOccupation.h"
#include "RPGTrait.h"

RPGOccupation::RPGOccupation(FName _name) : name(_name)
{
}

RPGOccupation::~RPGOccupation()
{
}

FName RPGOccupation::GetName() const
{
	return name;
}

void RPGOccupation::SetPrimaryStats(FName primary, FName secondary, FName tertiary)
{
	primaryStat = primary;
	secondaryStat = secondary;
	tertiaryStat = tertiary;
}

void RPGOccupation::GetPrimaryStats(FName& primary, FName& secondary, FName& tertiary) const
{
	primary = primaryStat;
	secondary = secondaryStat;
	tertiary = tertiaryStat;
}

void RPGOccupation::AddTrait(RPGTrait* trait, bool essential)
{
	ensure(trait != nullptr);

	if (essential)
	{
		ensure(!essentialTraits.Contains(trait));
		essentialTraits.Add(trait);
	}
	else
	{
		ensure(!optionalTraits.Contains(trait));
		optionalTraits.Add(trait);
	}
}

int RPGOccupation::TraitsCount(bool essential) const
{
	return essential ? essentialTraits.Num() : optionalTraits.Num();
}

RPGTrait* RPGOccupation::GetTrait(int index, bool essential) const
{
	ensure(index >= 0);
	ensure((essential && index < essentialTraits.Num()) || (!essential && index < optionalTraits.Num()));
	return essential ? essentialTraits[index] : optionalTraits[index];
}
