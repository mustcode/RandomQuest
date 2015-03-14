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

	enum StatPreference
	{
		Primary,
		Secondary,
		NiceToHave,
		NotImportant
	};

	RPGClass();
	~RPGClass();

	int GetStartingMaxHP() const;
	DiceType GetHitDice() const { return hitDice; }

protected:

	static const int MAX_SPELL_LEVEL = 9;

	DiceType hitDice;
	int savingThrowBonus[RPGAttributes::Stat::Count];
	StatPreference statsPreferences[RPGAttributes::Stat::Count];
	
	TArray<FName> armorProficiencies;
	TArray<FName> weaponProficiencies;

	TArray<RPGSpell*> availableSpells;
	int spellsKnownAtLevel[RPGAttributes::MAX_LEVEL+1];
	int spellSlotsAtLevel[RPGAttributes::MAX_LEVEL+1][MAX_SPELL_LEVEL+1];

	int numberOfStartingSkills;
	TArray<RPGSkill*> startingSkillsChoices;
	TArray<RPGInventory*> startingBackpackChoices;
	TArray<RPGItem*> startingArmorChoices;
	TArray<RPGItem*> startingPrimaryWeaponChoices;
	TArray<RPGItem*> startingSecondaryWeaponChoices;
	TArray<RPGItem*> startingItems;
};
