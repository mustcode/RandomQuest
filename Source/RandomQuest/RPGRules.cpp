// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGRules.h"
#include "RPGCharacter.h"
#include "RPGDice.h"

RPGRules::RPGRules() : gold(0)
{
}

RPGRules::~RPGRules()
{
}

void RPGRules::InitCharacter(RPGCharacter* character)
{
	const int MAX_ABILITY_SCORE = 10;
	character->AddAttribute("STR", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("DEX", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("CON", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("INT", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("WIS", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("CHR", 0, MAX_ABILITY_SCORE);

	RandomizeAttributes(character);

	int STR = character->GetAttribute("STR").GetValue();
	int DEX = character->GetAttribute("DEX").GetValue();
	int CON = character->GetAttribute("CON").GetValue();
	int INT = character->GetAttribute("INT").GetValue();
	int WIS = character->GetAttribute("WIS").GetValue();

	character->AddAttribute("PHY", 0, RPGDice::Roll(STR > DEX ? STR : DEX, D6)).SetValueToMax();
	character->AddAttribute("MNT", 0, RPGDice::Roll(INT > WIS ? INT : WIS, D6)).SetValueToMax();
	character->AddAttribute("HP", 0, RPGDice::Roll(CON, D6)).SetValueToMax();
}

bool RPGRules::AbilityTest(RPGCharacter* character, FName ability, int difficulty, int& result)
{
	int value = character->GetAttribute(ability).GetValue();
	result = RPGDice::Roll(value, D6, 4);
	return result >= difficulty;
}

bool RPGRules::AbilityTest(RPGCharacter* character, FName ability, int difficulty)
{
	int result;
	return AbilityTest(character, ability, difficulty, result);
}

void RPGRules::RandomizeAttributes(RPGCharacter* character)
{
	static const int NUM_STAT = 6;
	static const int NUM_DICE = 10;
	static const int MIN_TOTAL = 25;
	static const int MAX_TOTAL = 35;
	static const int MAX_REROLL = 10;
	static const FName attributes[] = { "STR", "DEX", "CON", "INT", "WIS", "CHR" };

	int total = 0;
	for (int i = 0; i < MAX_REROLL; ++i)
	{
		total = RPGDice::Roll(NUM_DICE, D6);
		if (total >= MIN_TOTAL && total <= MAX_TOTAL)
			break;
	}
	while(total > 0)
	{
		RPGAttribute& attribute = character->GetAttribute(attributes[FMath::RandRange(0, NUM_STAT - 1)]);
		if (attribute.GetValue() >= attribute.GetMaxValue())
			continue;
		attribute.Increase(1);
		--total;
	}
}
