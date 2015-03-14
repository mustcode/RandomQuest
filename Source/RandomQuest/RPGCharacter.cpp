// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGCharacter.h"

#include "RPGRace.h"
#include "RPGClass.h"
#include "RPGAttributes.h"
#include "RPGInventory.h"
#include "RPGWeapon.h"
#include "RPGAppearance.h"

RPGCharacter::RPGCharacter() :
	race(nullptr),
	primaryClass(nullptr),
	secondaryClass(nullptr),
	attributes(nullptr),
	inventory(nullptr),
	appearance(nullptr)
{
}

RPGCharacter::~RPGCharacter()
{
	if (race)
		delete race;
	if (primaryClass)
		delete primaryClass;
	if (secondaryClass)
		delete secondaryClass;
	if (attributes)
		delete attributes;
	if (inventory)
		delete inventory;
	if (appearance)
		delete appearance;
}

void RPGCharacter::Randomize()
{
	if(attributes)
		delete attributes;
	attributes = new RPGAttributes;
	attributes->Randomize();

	RandomizeName();
}

int RPGCharacter::GetArmorClass() const
{
	return 0;
}

int RPGCharacter::RollToHit() const
{
	return 0;
}

int RPGCharacter::RollForDamage() const
{
	return 0;
}

RPGWeapon* RPGCharacter::GetCurrentWeapon() const
{
	return nullptr;
}

void RPGCharacter::RandomizeName()
{
	title = TEXT("RamdomTitle");
	firstName = TEXT("RamdomFirstName");
	middleName = TEXT("RandomMiddleName");
	lastName = TEXT("RamdomLastName");
}
