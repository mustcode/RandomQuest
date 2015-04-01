// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGAttributes.h"
#include "RPGDice.h"

RPGAttributes::RPGAttributes()
{
}

RPGAttributes::~RPGAttributes()
{
}

void RPGAttributes::Randomize()
{
	int rolls[Stat::Count];
	int total = 0;
	int minimum = Stat::Count * 4;
	while (total < minimum)
		total = RPGDice::Roll(Stat::Count, D6, rolls);
	for (int i = 0; i < Stat::Count; ++i)
		stats[i] = rolls[i];
	
	int minHP = stats[Stat::CON];
	int baseHP = RPGDice::Roll(stats[Stat::CON], D6);
	int bonusHP = RPGDice::Roll(stats[Stat::CON], D6, 4);
	maxHP = minHP + baseHP + bonusHP;
	HP = maxHP;
}

int RPGAttributes::GetStat(Stat stat) const
{
	return stats[stat];
}
