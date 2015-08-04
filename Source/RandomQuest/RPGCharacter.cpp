// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGCharacter.h"

#include "RPGRace.h"
#include "RPGInventory.h"
#include "RPGWeapon.h"
#include "RPGAppearance.h"
#include "RPGSkill.h"
#include "RPGTrait.h"

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

RPGAttribute* RPGCharacter::AddAttribute(FName name, int minValue, int maxValue)
{
	RPGAttribute attribute(name, minValue, maxValue);
	attributes.Add(name, attribute);
	return &attributes[name];
}

RPGAttribute* RPGCharacter::GetAttribute(FName name)
{
	ensure(attributes.Contains(name));
	return &attributes[name];
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

bool RPGCharacter::HasSkill(RPGSkill* skill) const
{
	ensure(skill != nullptr);
	return skills.Contains(skill);
}

bool RPGCharacter::HasSkill(FName name) const
{
	return skills.ContainsByPredicate([&](RPGSkill* skill){ return skill->GetName() == name; });
}

RPGSkill* RPGCharacter::GetSkill(FName name) const
{
	auto result = skills.FindByPredicate([&](RPGSkill* skill){ return skill->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

void RPGCharacter::AddTrait(RPGTrait* trait)
{
	ensure(!traits.Contains(trait));
	traits.Add(trait);
}

bool RPGCharacter::HasTrait(RPGTrait* trait) const
{
	ensure(trait != nullptr);
	return traits.Contains(trait);
}

bool RPGCharacter::HasTrait(FName name) const
{
	return traits.ContainsByPredicate([&](RPGTrait* trait){ return trait->GetName() == name; });
}

RPGTrait* RPGCharacter::GetTrait(FName name) const
{
	auto result = traits.FindByPredicate([&](RPGTrait* trait){ return trait->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

void RPGCharacter::DebugDump() const
{
}
