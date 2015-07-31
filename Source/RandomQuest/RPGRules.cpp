// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGRules.h"
#include "RPGCharacter.h"
#include "RPGSkill.h"
#include "RPGTrait.h"
#include "RPGRace.h"
#include "RPGOccupation.h"
#include "RPGDice.h"

RPGRules::RPGRules()
{
}

RPGRules::~RPGRules()
{
}

void RPGRules::RandomizeStats(RPGCharacter* character)
{
	const int MAX_ABILITY_SCORE = 10;
	character->AddAttribute("STR", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("DEX", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("CON", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("INT", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("WIS", 0, MAX_ABILITY_SCORE);
	character->AddAttribute("CHR", 0, MAX_ABILITY_SCORE);

	RandomizeAttributes(character);

	int STR = character->GetAttribute("STR")->GetValue();
	int DEX = character->GetAttribute("DEX")->GetValue();
	int CON = character->GetAttribute("CON")->GetValue();
	int INT = character->GetAttribute("INT")->GetValue();
	int WIS = character->GetAttribute("WIS")->GetValue();

	character->AddAttribute("PHY", 0, RPGDice::Roll(STR > DEX ? STR : DEX, D6))->SetValueToMax();
	character->AddAttribute("MNT", 0, RPGDice::Roll(INT > WIS ? INT : WIS, D6))->SetValueToMax();
	character->AddAttribute("HP", 0, RPGDice::Roll(CON, D6))->SetValueToMax();
}

void RPGRules::AssignRace(RPGCharacter* character, TArray<RPGRace*>& races)
{
	ensure(races.Num() > 0);
	int randomIndex = FMath::RandRange(0, static_cast<int>(races.Num() - 1));
	RPGRace* race = races[randomIndex];
	for (int i = 0; i < race->TraitsCount(); ++i)
		character->AddTrait(race->GetTrait(i));
}

void RPGRules::AssignOccupation(RPGCharacter* character, TArray<RPGOccupation*>& occupations)
{
	ensure(occupations.Num() > 0);
	RPGOccupation* occupation = GetMostSuitableOccupation(character, occupations);
	ensure(occupation != nullptr);

	for (int i = 0; i < occupation->TraitsCount(true); ++i)
		character->AddTrait(occupation->GetTrait(i, true));

	TArray<RPGTrait*> optionalTraits;
	for (int i = 0; i < occupation->TraitsCount(false); ++i)
		optionalTraits.Add(occupation->GetTrait(i, false));
	int removeCount = occupation->TraitsCount(false) / 2;
	for (int i = 0; i < removeCount; ++i)
	{
		int randomIndex = FMath::RandRange(0, static_cast<int>(optionalTraits.Num()-1));
		optionalTraits.RemoveAtSwap(randomIndex);
	}
	for (auto trait : optionalTraits)
		character->AddTrait(trait);
}

bool RPGRules::AbilityTest(RPGCharacter* character, FName ability, int difficulty, int& result)
{
	int value = character->GetAttribute(ability)->GetValue();
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
		RPGAttribute* attribute = character->GetAttribute(attributes[FMath::RandRange(0, NUM_STAT - 1)]);
		if (attribute->GetValue() >= attribute->GetMaxValue())
			continue;
		attribute->Increase(1);
		--total;
	}
}

RPGOccupation* RPGRules::GetMostSuitableOccupation(RPGCharacter* character, TArray<RPGOccupation*>& occupations) const
{
	const int ATTRIBUTES_COUNT = 6;
	TArray<TPair<int, RPGAttribute*>> attributes;
	attributes.AddDefaulted(ATTRIBUTES_COUNT);

	attributes[0].Value = character->GetAttribute("STR");
	attributes[1].Value = character->GetAttribute("DEX");
	attributes[2].Value = character->GetAttribute("CON");
	attributes[3].Value = character->GetAttribute("INT");
	attributes[4].Value = character->GetAttribute("WIS");
	attributes[5].Value = character->GetAttribute("CHR");
	attributes.Sort([](const TPair<int, RPGAttribute*>& a, const TPair<int, RPGAttribute*>& b){ return a.Value->GetValue() > b.Value->GetValue(); });

	attributes[0].Key = 1;
	for (int i = 1, currentRank = 1, currentScore = attributes[0].Value->GetValue(); i < attributes.Num(); ++i)
	{
		int score = attributes[i].Value->GetValue();
		if (score < currentScore)
		{
			currentScore = score;
			++currentRank;
		}
		attributes[i].Key = currentRank;
	}

	TMap<FName, TPair<int, RPGAttribute*>> attributesLookup;
	for (auto attribute : attributes)
		attributesLookup.Add(attribute.Value->GetName(), attribute);

	int mostSuitable = MAX_int8;
	RPGOccupation* result = nullptr;
	for (auto occupation : occupations)
	{
		FName primary, secondary, tertiary;
		occupation->GetPrimaryStats(primary, secondary, tertiary);
		int suitability = attributesLookup[primary].Key + attributesLookup[secondary].Key + attributesLookup[tertiary].Key;
		if (suitability < mostSuitable)
		{
			mostSuitable = suitability;
			result = occupation;
		}
	}
	return result;
}
