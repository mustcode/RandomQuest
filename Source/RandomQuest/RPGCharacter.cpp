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
	attributes = new RPGAttributes;
	attributes->Randomize();
}

void RPGCharacter::DebugDump() const
{
	UE_LOG(LogTemp, Warning, TEXT("NAME %s"), *firstName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("STR %d"), attributes->GetStat(RPGAttributes::STR));
	UE_LOG(LogTemp, Warning, TEXT("DEX %d"), attributes->GetStat(RPGAttributes::DEX));
	UE_LOG(LogTemp, Warning, TEXT("CON %d"), attributes->GetStat(RPGAttributes::CON));
	UE_LOG(LogTemp, Warning, TEXT("INT %d"), attributes->GetStat(RPGAttributes::INT));
	UE_LOG(LogTemp, Warning, TEXT("WIS %d"), attributes->GetStat(RPGAttributes::WIS));
	UE_LOG(LogTemp, Warning, TEXT("CHA %d"), attributes->GetStat(RPGAttributes::CHA));
}
