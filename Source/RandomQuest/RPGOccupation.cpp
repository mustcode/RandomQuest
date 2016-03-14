// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGOccupation.h"
#include "RPGTrait.h"
#include "RPGSkill.h"

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

void RPGOccupation::SetStatPreference(FName attribute, float weight)
{
	ensure(!statPreferences.Contains(attribute));
	statPreferences.Add(attribute, weight);
}

float RPGOccupation::GetStatPreference(FName attribute) const
{
	return (statPreferences.Contains(attribute)) ? statPreferences[attribute] : 0.f;
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

const TArray<RPGTrait*>& RPGOccupation::GetEssentialTraits() const
{
	return essentialTraits;
}

const TArray<RPGTrait*>& RPGOccupation::GetOptionalTraits() const
{
	return optionalTraits;
}

void RPGOccupation::AddStartingSkill(RPGSkill* skill)
{
	ensure(!startingSkills.Contains(skill));
	startingSkills.Add(skill);
}

const TArray<RPGSkill*>& RPGOccupation::GetStartingSkills() const
{
	return startingSkills;
}
