// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGAttributes.h"
#include "RPGDice.h"

int RPGAttributes::expTable[] =
{
	0,
	0,
	300,
	900,
	2700,
	6500,
	14000,
	23000,
	34000,
	48000,
	64000,
	85000,
	100000,
	120000,
	140000,
	165000,
	195000,
	225000,
	265000,
	305000,
	355000
};

int RPGAttributes::proficiencyBonusTable[] =
{
	0,
	2,
	2,
	2,
	2,
	3,
	3,
	3,
	3,
	4,
	4,
	4,
	4,
	5,
	5,
	5,
	5,
	6,
	6,
	6,
	6
};

RPGAttributes::RPGAttributes()
{
}

RPGAttributes::~RPGAttributes()
{
}

int RPGAttributes::GetStat(Stat stat) const
{
	return stats[stat];
}

int RPGAttributes::GetModifier(Stat stat) const
{
	return FPlatformMath::RoundToInt(((stats[stat] - 10.f) / 2.f) - 0.1f);
}

int RPGAttributes::GetProficiencyBonus() const
{
	return proficiencyBonusTable[level];
}

void RPGAttributes::Randomize()
{
	int level = 1;
	for (int i = 0; i < Stat::Count; ++i)
	{
		TArray<int> results;
		RPGDice::Roll(4, D6, results);
		results.Sort();
		stats[i] = results[1] + results[2] + results[3];
	}
}

void RPGAttributes::AddRaceBonus(const int raceBonus[Stat::Count])
{
	for (int i = 0; i < Stat::Count; ++i)
		stats[i] += raceBonus[i];
}

bool RPGAttributes::AddExp(int expPoints)
{
	ensure(exp >= expTable[level]);
	exp += expPoints;
	return CanLevelUp();
}

bool RPGAttributes::CanLevelUp() const
{
	return level < MAX_LEVEL && exp >= expTable[level + 1];
}

void RPGAttributes::LevelUp(DiceType hitDice, const int statsIncrease[Stat::Count])
{
	++level;
	int currentCONMod = GetModifier(Stat::CON);
	for (int i = 0; i < Stat::Count; ++i)
		stats[i] += statsIncrease[i];
	int newCONMod = GetModifier(Stat::CON);
	if (newCONMod > currentCONMod)
		maxHP += level;
	maxHP += RPGDice::Roll(1, hitDice) + GetModifier(Stat::CON);
}
