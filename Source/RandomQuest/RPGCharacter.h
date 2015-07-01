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
	void AddAttribute(FName name, int minValue, int maxValue);
	RPGAttribute& GetAttribute(FName name);
	int GetAttributeValue(FName name) const;
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

	TMap<FName, RPGAttribute> attributes;
};
