// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGAttributes.h"
#include "RPGDice.h"

class RPGSkill;
class RPGSpell;
class RPGInventory;
class RPGItem;

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

	StatPreference statsPreferences[RPGAttributes::Stat::Count];
};
