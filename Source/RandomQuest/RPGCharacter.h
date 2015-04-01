// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGDice.h"
#include "RPGAlignment.h"

class RPGRace;
class RPGClass;
class RPGAttributes;
class RPGInventory;
class RPGWeapon;
class RPGAppearance;
class RPGSkill;
class RPGSpell;
class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGCharacter
{
public:

	enum Gender
	{
		Male,
		Female
	};

	RPGCharacter();
	~RPGCharacter();
	void Randomize();
	void DebugDump() const;

protected:
	FName title;
	FName firstName;
	FName middleName;
	FName lastName;
	Gender gender;
	RPGRace* race;
	RPGClass* primaryClass;
	RPGClass* secondaryClass;
	RPGAttributes* attributes;
	RPGAppearance* appearance;
	RPGAlignment alignment;
	RPGInventory* inventory;
	TArray<RPGTrait*> traits;
	TArray<RPGSkill*> skills;
	TArray<RPGSpell*> spells;
};
