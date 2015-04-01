// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGAttributes.h"
#include "RPGDice.h"

class RPGSkill;
class RPGSpell;
class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGClass
{
public:

	RPGClass();
	~RPGClass();

protected:

	enum StatPreference
	{
		Primary,
		Secondary,
		NiceToHave,
		NotImportant
	};

	FName name;
	StatPreference statsPreferences[RPGAttributes::Stat::Count];
	TArray<RPGTrait*> traits;
	TArray<RPGSkill*> skills;
	TArray<RPGSpell*> spells;
};
