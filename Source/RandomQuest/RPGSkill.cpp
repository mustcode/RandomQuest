// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGSkill.h"

RPGSkill::RPGSkill(FName _name, FName _variationOf, bool _isNonCombatSkill)
	: name(_name)
	, variationOf(_variationOf)
	, isNonCombatSkill(_isNonCombatSkill)
{
}

RPGSkill::~RPGSkill()
{
}

FName RPGSkill::GetName() const
{
	return name;
}

FName RPGSkill::GetVariationOf() const
{
	return variationOf;
}

bool RPGSkill::IsNonCombatSkill() const
{
	return isNonCombatSkill;
}

void RPGSkill::AddCommand(FName command, float time, float value)
{
	commands.Add(Command(command, time, value));
}

void RPGSkill::AddCommand(Command command)
{
	commands.Add(command);
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

const TArray<RPGSkill::Command>& RPGSkill::GetCommands() const
{
	return commands;
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

const TMap<FName, int>& RPGSkill::GetCosts() const
{
	return costs;
}
