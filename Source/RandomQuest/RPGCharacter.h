// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGDice.h"

class RPGRace;
class RPGClass;
class RPGAttributes;
class RPGInventory;
class RPGWeapon;
class RPGAppearance;

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
	RPGInventory* inventory;
	RPGAppearance* appearance;
};
