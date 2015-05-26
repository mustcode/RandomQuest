// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGAlignment.h"
#include "RPGAttribute.h"

class RPGRace;
class RPGClass;
class RPGInventory;
class RPGWeapon;
class RPGAppearance;
class RPGSkill;
class RPGTrait;
class RPGAbnormality;

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
	RPGAppearance* appearance;
	RPGAlignment alignment;
	RPGInventory* inventory;
	
	TArray<RPGTrait*> traits;
	TArray<RPGSkill*> skills;
	TArray<RPGAbnormality*> abnormalities;

	RPGAttribute hp;
	RPGAttribute exp;
	RPGAttribute level;
	TMap<FName, RPGAttribute> attributes;
	TMap<FName, RPGAttribute> statuses;
};
