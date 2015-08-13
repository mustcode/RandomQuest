// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGRules.h"
#include "RPGCharacter.h"
#include "RPGSkill.h"
#include "RPGTrait.h"
#include "RPGRace.h"
#include "RPGOccupation.h"
#include "RPGDice.h"
#include "RPGPrerequisite.h"

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

	int traitsToAdd = RPGDice::Roll(D6);
	if (traitsToAdd > optionalTraits.Num())
		traitsToAdd = optionalTraits.Num();
	for (int i = 0; i < traitsToAdd; ++i)
	{
		int randomIndex = FMath::RandRange(0, optionalTraits.Num()-1);
		character->AddTrait(optionalTraits[randomIndex]);
		optionalTraits.RemoveAtSwap(randomIndex);
	}
}

void RPGRules::RandomizeCommonTraits(RPGCharacter* character, TArray<RPGTrait*>& traits)
{
	const FName COMMON_TRAIT("Common");

	TArray<RPGTrait*> commonTraits;
	for (auto trait : traits)
	{
		if (trait->HasProperty(COMMON_TRAIT))
			commonTraits.Add(trait);
	}

	int traitsToAdd = RPGDice::Roll(D6);
	if (traitsToAdd > commonTraits.Num())
		traitsToAdd = commonTraits.Num();
	for (int i = 0; i < traitsToAdd; ++i)
	{
		int randomIndex = FMath::RandRange(0, commonTraits.Num()-1);
		character->AddTrait(commonTraits[randomIndex]);
		commonTraits.RemoveAtSwap(randomIndex);
	}
}

bool RPGRules::MeetPrerequisite(RPGCharacter* character, RPGPrerequisite* prerequisite) const
{
	for (auto trait : prerequisite->RequiredTraits)
	{
		if (!character->HasTrait(trait))
			return false;
	}
	for (auto trait : prerequisite->BannedTraits)
	{
		if (character->HasTrait(trait))
			return false;
	}
	for (auto minimumStat : prerequisite->MinimumStats)
	{
		FName attribute = minimumStat.Key;
		int scoreRequired = minimumStat.Value;
		if (character->GetAttributeValue(attribute) < scoreRequired)
			return false;
	}
	return true;
}

bool RPGRules::CanUseSkill(RPGCharacter* character, RPGSkill* skill) const
{
	ensure(character != nullptr);
	ensure(skill != nullptr);
	ensure(character->HasSkill(skill));

	const FName PHY("PHY");
	const FName MNT("MNT");

	int PHYCost = skill->GetCost(PHY);
	int MNTCost = skill->GetCost(MNT);
	int currentPHY = character->GetAttributeValue(PHY);
	int currentMNT = character->GetAttributeValue(MNT);

	return currentPHY >= PHYCost && currentMNT >= MNTCost;
}

void RPGRules::DeductSkillCost(RPGCharacter* character, RPGSkill* skill)
{
	ensure(CanUseSkill(character, skill));

	const FName PHY("PHY");
	const FName MNT("MNT");

	character->GetAttribute(PHY)->Decrease(skill->GetCost(PHY));
	character->GetAttribute(MNT)->Decrease(skill->GetCost(MNT));
}

bool RPGRules::AbilityTest(RPGCharacter* character, FName ability, int difficulty, int& result) const
{
	int value = character->GetAttribute(ability)->GetValue();
	result = RPGDice::Roll(value, D6, 4);
	return result >= difficulty;
}

bool RPGRules::AbilityTest(RPGCharacter* character, FName ability, int difficulty) const
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

	ensure(occupations.Num() > 0);
	int mostSuitable = 0;
	TArray<RPGOccupation*> results;
	for (auto occupation : occupations)
	{
		float suitability = 0;
		for (auto attribute : attributes)
		{
			float weight = occupation->GetStatPreference(attribute.Value->GetName());
			int rank = attribute.Key;
			suitability += (ATTRIBUTES_COUNT - rank) * weight;
		}
		if (suitability > mostSuitable)
		{
			mostSuitable = suitability;
			results.Empty();
			results.Add(occupation);
		}
		else if (suitability == mostSuitable)
		{
			results.Add(occupation);
		}
	}
	ensure(results.Num() > 0);
	return results[FMath::RandRange(0, results.Num()-1)];
}
