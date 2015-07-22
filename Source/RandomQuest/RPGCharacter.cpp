// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGCharacter.h"

#include "RPGRace.h"
#include "RPGClass.h"
#include "RPGInventory.h"
#include "RPGWeapon.h"
#include "RPGAppearance.h"

RPGCharacter::RPGCharacter() :
	inventory(nullptr),
	appearance(nullptr)
{
}

RPGCharacter::~RPGCharacter()
{
	if (inventory)
		delete inventory;
	if (appearance)
		delete appearance;
}

RPGAttribute& RPGCharacter::AddAttribute(FName name, int minValue, int maxValue)
{
	RPGAttribute attribute(name, minValue, maxValue);
	attributes.Add(name, attribute);
	return attributes[name];
}

RPGAttribute& RPGCharacter::GetAttribute(FName name)
{
	ensure(attributes.Contains(name));
	return attributes[name];
}

int RPGCharacter::GetAttributeValue(FName name) const
{
	ensure(attributes.Contains(name));
	return attributes[name].GetValue();
}

void RPGCharacter::AddSkill(RPGSkill* skill)
{
	ensure(!skills.Contains(skill));
	skills.Add(skill);
}

void RPGCharacter::DebugDump() const
{
}
