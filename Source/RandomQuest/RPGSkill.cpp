// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGSkill.h"

RPGSkill::RPGSkill()
{
}

RPGSkill::~RPGSkill()
{
}

void RPGSkill::SetName(FName toSet)
{
	name = toSet;
}

void RPGSkill::SetVariationOf(FName toSet)
{
	variationOf = toSet;
}

FName RPGSkill::GetName() const
{
	return name;
}

FName RPGSkill::GetVariationOf() const
{
	return variationOf;
}

void RPGSkill::AddCommand(FName command, float value)
{
	commands.Add(Command(command, value));
}

int RPGSkill::CommandsCount() const
{
	return commands.Num();
}

const RPGSkill::Command& RPGSkill::GetCommand(int index) const
{
	ensure(index >= 0 && index < commands.Num());
	return commands[index];
}

void RPGSkill::AddRequirement(FName need, int amount)
{
	requirements.Add(Requirement(need, amount));
}

int RPGSkill::RequirementsCount() const
{
	return requirements.Num();
}

const RPGSkill::Requirement& RPGSkill::GetRequirement(int index) const
{
	ensure(index >= 0 && index < requirements.Num());
	return requirements[index];
}

void RPGSkill::AddCost(FName resource, int value)
{
	ensure(!costs.Contains(resource));
	costs.Add(resource, value);
}

int RPGSkill::GetCost(FName resource) const
{
	return (costs.Contains(resource)) ? costs[resource] : 0;
}
