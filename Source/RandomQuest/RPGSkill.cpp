// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGSkill.h"

RPGSkill::RPGSkill(FText _displayName, FText _description, FName _name, FName _variationOf, bool _isUsableInCombat, bool _isUsableOutOfCombat, bool _canSelectTargetAlly, bool _canSelectTargetEnemy)
	: displayName(_displayName)
	, description(_description)
	, name(_name)
	, variationOf(_variationOf)
	, isUsableInCombat(_isUsableInCombat)
	, isUsableOutOfCombat(_isUsableOutOfCombat)
	, canSelectTargetAlly(_canSelectTargetAlly)
	, canSelectTargetEnemy(_canSelectTargetEnemy)
{
}

RPGSkill::~RPGSkill()
{
}

FText RPGSkill::GetDisplayName() const
{
	return displayName;
}

FText RPGSkill::GetDescription() const
{
	return description;
}

FName RPGSkill::GetName() const
{
	return name;
}

FName RPGSkill::GetVariationOf() const
{
	return variationOf;
}

bool RPGSkill::IsUsableInCombat() const
{
	return isUsableInCombat;
}

bool RPGSkill::IsUsableOutOfCombat() const
{
	return isUsableOutOfCombat;
}

bool RPGSkill::CanSelectTargetAlly() const
{
	return canSelectTargetAlly;
}

bool RPGSkill::CanSelectTargetEnemy() const
{
	return canSelectTargetEnemy;
}

void RPGSkill::AddCommand(FName command, FName param, float time, float value)
{
	commands.Add(Command(command, param, time, value));
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
