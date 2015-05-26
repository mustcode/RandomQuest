// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGCharacter.h"

#include "RPGRace.h"
#include "RPGClass.h"
#include "RPGInventory.h"
#include "RPGWeapon.h"
#include "RPGAppearance.h"

RPGCharacter::RPGCharacter() :
	race(nullptr),
	primaryClass(nullptr),
	secondaryClass(nullptr),
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
	if (inventory)
		delete inventory;
	if (appearance)
		delete appearance;
}

void RPGCharacter::Randomize()
{
}

void RPGCharacter::DebugDump() const
{
}
