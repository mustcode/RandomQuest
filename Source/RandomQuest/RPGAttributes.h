// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGDice.h"

/**
 * 
 */
class RANDOMQUEST_API RPGAttributes
{
public:

	enum Stat
	{
		STR,
		DEX,
		CON,
		INT,
		WIS,
		CHA,
		Count
	};

	static const int MAX_LEVEL = 20;

	RPGAttributes();
	~RPGAttributes();

	int GetStat(Stat stat) const;
	int GetModifier(Stat stat) const;
	int GetProficiencyBonus() const;

	int GetLevel() const { return level; }
	int GetExp() const { return exp; }
	int GetHP() const { return HP; }
	int GetMaxHP() const { return maxHP; }

	void Randomize();
	void AddRaceBonus(const int raceBonus[Stat::Count]);
	bool AddExp(int expPoints);
	bool CanLevelUp() const;
	void LevelUp(DiceType hitDice, const int statsIncrease[Stat::Count]);

protected:

	static int expTable[MAX_LEVEL + 1];
	static int proficiencyBonusTable[MAX_LEVEL + 1];

	int stats[Stat::Count];
	int level;
	int exp;
	int HP;
	int maxHP;
};
