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
#include "RPGEquipSlot.h"
#include "RPGItem.h"
#include "RPGItemInstance.h"
#include "RPGCombatRating.h"

RPGRules::RPGRules()
{
}

RPGRules::~RPGRules()
{
}

TArray<FName> RPGRules::GetPrimaryStats() const
{
	TArray<FName> stats;
	stats.Add("STR");
	stats.Add("DEX");
	stats.Add("CON");
	stats.Add("INT");
	stats.Add("WIS");
	stats.Add("CHR");
	return stats;
}

int32 RPGRules::GetVariableStats(FName& stat1, FName& stat2, FName& stat3, FName& stat4, FName& stat5) const
{
	stat1 = "HP";
	stat2 = "PHY";
	stat3 = "MNT";
	stat4 = NAME_None;
	stat5 = NAME_None;
	return 3;
}

void RPGRules::RandomizeStats(RPGCharacter* character)
{
	const int MAX_ABILITY_SCORE = 10;
	TArray<FName> stats = GetPrimaryStats();
	for (auto stat : stats)
		character->AddAttribute(stat, 0, MAX_ABILITY_SCORE);

	RandomizeAttributes(character);

	int STR = character->GetAttribute("STR")->GetValue();
	int DEX = character->GetAttribute("DEX")->GetValue();
	int CON = character->GetAttribute("CON")->GetValue();
	int INT = character->GetAttribute("INT")->GetValue();
	int WIS = character->GetAttribute("WIS")->GetValue();

	character->AddAttribute("PHY", 0, RPGDice::Roll(STR > DEX ? STR : DEX, D6))->SetValueToMax();
	character->AddAttribute("MNT", 0, RPGDice::Roll(INT > WIS ? INT : WIS, D6))->SetValueToMax();
	character->AddAttribute("HP", 0, RPGDice::Roll(CON, D6))->SetValueToMax();

	const float PHY_RECHARGE_RATE = 5.f;
	const float MNT_RECHARGE_RATE = 5.f;
	character->AddTimer("PHY_RCH", PHY_RECHARGE_RATE);
	character->AddTimer("MNT_RCH", MNT_RECHARGE_RATE);
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
		if (character->GetAttribute(attribute)->GetValue() < scoreRequired)
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
	int currentPHY = character->GetAttribute(PHY)->GetValue();
	int currentMNT = character->GetAttribute(MNT)->GetValue();

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

int RPGRules::ApplyHealing(RPGCharacter* healer, RPGCharacter* receiver, int amount, FName healingType, bool& isCritical, bool& isFumbled)
{
	amount = CheckForCritical(amount, isCritical, isFumbled);
	receiver->GetAttribute("HP")->Increase(amount);
	return amount;
}

int RPGRules::ApplyDamage(RPGCharacter* instigator, RPGCharacter* victim, int amount, FName damageType, bool& isCritical, bool& isFumbled)
{
	amount = CheckForCritical(amount, isCritical, isFumbled);
	victim->GetAttribute("HP")->Decrease(amount);
	return amount;
}

void RPGRules::CalculateCombatRating(RPGCombatRating* combatRating)
{
	ensure(combatRating != nullptr);
	ensure(combatRating->character != nullptr);

	combatRating->attack = 0;
	combatRating->attackBonus = 0;
	combatRating->defense = 0;
	combatRating->defenseBonus = 0;
	combatRating->damage = 0;
	combatRating->damageBonus = 0;

	auto character = combatRating->character;
	for (auto trait : character->GetTraits())
	{
		for (auto prop : trait->GetProperties())
		{
			if (prop.Key == "AttackModifier")
				combatRating->attack += prop.Value.value;
			else if (prop.Key == "AttackModifierFromAttribute")
				combatRating->attack += character->GetAttribute(prop.Value.key)->GetValue() - prop.Value.value;
			else if (prop.Key == "AttackBonusModifier")
				combatRating->attackBonus += prop.Value.value;
			else if (prop.Key == "AttackBonusModifierFromAttribute")
				combatRating->attackBonus += character->GetAttribute(prop.Value.key)->GetValue() - prop.Value.value;

			else if (prop.Key == "DefenseModifier")
				combatRating->defense += prop.Value.value;
			else if (prop.Key == "DefenseModifierFromAttribute")
				combatRating->defense += character->GetAttribute(prop.Value.key)->GetValue() - prop.Value.value;
			else if (prop.Key == "DefenseBonusModifier")
				combatRating->defenseBonus += prop.Value.value;
			else if (prop.Key == "DefenseBonusModifierFromAttribute")
				combatRating->defenseBonus += character->GetAttribute(prop.Value.key)->GetValue() - prop.Value.value;

			else if (prop.Key == "DamageModifier")
				combatRating->damage += prop.Value.value;
			else if (prop.Key == "DamageModifierFromAttribute")
				combatRating->damage += character->GetAttribute(prop.Value.key)->GetValue() - prop.Value.value;
			else if (prop.Key == "DamageBonusModifier")
				combatRating->damageBonus += prop.Value.value;
			else if (prop.Key == "DamageBonusModifierFromAttribute")
				combatRating->damageBonus += character->GetAttribute(prop.Value.key)->GetValue() - prop.Value.value;
		}
	}

	auto equipments = combatRating->equipments;
	TArray<RPGItem*> weapons;
	for (auto item : equipments)
	{
		RPGItem* rpgItem = item->GetItem();
		combatRating->defense += rpgItem->GetProtection();
		combatRating->damage += rpgItem->GetDamage();

		FName itemCategory = rpgItem->GetCategory();
		if (itemCategory == "Weapon")
		{
			combatRating->attack += GetAttackValueFromWeapon(character, rpgItem);
			weapons.Add(rpgItem);
		}

		FName itemType = rpgItem->GetType();
		FName itemSubType = rpgItem->GetSubType();
		for (auto trait : character->GetTraits())
		{
			for (auto prop : trait->GetProperties())
			{
				if (prop.Key == "AttackModifierFromItemType" && itemType == prop.Value.key)
					combatRating->attack += prop.Value.value;
				else if (prop.Key == "AttackModifierFromItemSubType" && itemSubType == prop.Value.key)
					combatRating->attack += prop.Value.value;
				else if (prop.Key == "AttackBonusModifierFromItemType" && itemType == prop.Value.key)
					combatRating->attackBonus += prop.Value.value;
				else if (prop.Key == "AttackBonusModifierFromItemSubType" && itemSubType == prop.Value.key)
					combatRating->attackBonus += prop.Value.value;

				else if (prop.Key == "DefenseModifierFromItemType" && itemType == prop.Value.key)
					combatRating->defense += prop.Value.value;
				else if (prop.Key == "DefenseModifierFromItemSubType" && itemSubType == prop.Value.key)
					combatRating->defense += prop.Value.value;
				else if (prop.Key == "DefenseBonusModifierFromItemType" && itemType == prop.Value.key)
					combatRating->defenseBonus += prop.Value.value;				
				else if (prop.Key == "DefenseBonusModifierFromItemSubType" && itemSubType == prop.Value.key)
					combatRating->defenseBonus += prop.Value.value;

				else if (prop.Key == "DamageModifierFromItemType" && itemType == prop.Value.key)
					combatRating->damage += prop.Value.value;
				else if (prop.Key == "DamageModifierFromItemSubType" && itemSubType == prop.Value.key)
					combatRating->damage += prop.Value.value;
				else if (prop.Key == "DamageBonusModifierFromItemType" && itemType == prop.Value.key)
					combatRating->damageBonus += prop.Value.value;
				else if (prop.Key == "DamageBonusModifierFromItemSubType" && itemSubType == prop.Value.key)
					combatRating->damageBonus += prop.Value.value;
			}
		}

		int weaponsLimit = HasTraitWithProperty(character->GetTraits(), "DualWeapons") ? 2 : 1;
		if (weapons.Num() > weaponsLimit)
		{
			for (auto weapon : weapons)
			{
				if (IsLightWeapon(weapon))
					continue;
				if (IsHeavyWeapon(weapon))
				{
					combatRating->attack -= 10;
					continue;
				}
				combatRating->attack -= 3;
				continue;
			}
		}
	}
}

int RPGRules::GetAttackValueFromWeapon(RPGCharacter* character, RPGItem* weapon) const
{
	ensure(weapon->GetCategory() == "Weapon");

	for (auto trait : weapon->GetTraits())
	{
		for (auto prop : trait->GetProperties())
		{
			if (prop.Key != "RequireAttribute")
				continue;

			int attributeScore = 0;
			if (prop.Value.key == "Finesse")
			{
				int STR = character->GetAttribute("STR")->GetValue();
				int DEX = character->GetAttribute("DEX")->GetValue();
				attributeScore = (STR > DEX) ? STR : DEX;
			}
			else
			{
				attributeScore = character->GetAttribute(prop.Value.key)->GetValue();
			}

			if (attributeScore > 6)
				return attributeScore - 6;
			if (attributeScore < 4)
				return attributeScore - 4;
			return 0;
		}
	}
	return 0;
}

bool RPGRules::IsLightWeapon(RPGItem* weapon) const
{
	ensure(weapon->GetCategory() == "Weapon");
	return HasTraitWithProperty(weapon->GetTraits(), "Light");
}

bool RPGRules::IsHeavyWeapon(RPGItem* weapon) const
{
	ensure(weapon->GetCategory() == "Weapon");
	return HasTraitWithProperty(weapon->GetTraits(), "Heavy");
}

int RPGRules::NormalAttack(RPGCombatRating* attacker, RPGCombatRating* defender, bool& isCritical, bool& isFumbled)
{
	int attack = RPGDice::Roll(FMath::Max(attacker->attack, 1), D6, 4) + attacker->attackBonus;
	int defense = RPGDice::Roll(FMath::Max(defender->defense, 1), D6, 4) + defender->defenseBonus;
	if (attack <= defense)
		return 0;
	int damage = RPGDice::Roll(FMath::Max(attacker->damage, 1), D6, 4) + attacker->damageBonus;
	return ApplyDamage(attacker->character, defender->character, damage, attacker->damageType, isCritical, isFumbled);
}

bool RPGRules::IsDead(RPGCharacter* character) const
{
	return character->GetAttribute("HP")->GetValue() <= 0;
}

void RPGRules::UpdateCharacter(float deltaSeconds, RPGCharacter* character)
{
	ensure(!IsDead(character));

	int phyRecharge = character->GetTimer("PHY_RCH")->Update(deltaSeconds);
	if (phyRecharge > 0)
		character->GetAttribute("PHY")->Increase(phyRecharge);
	
	int mntRecharge = character->GetTimer("MNT_RCH")->Update(deltaSeconds);
	if (mntRecharge > 0)
		character->GetAttribute("MNT")->Increase(mntRecharge);
}

void RPGRules::SetDefaultFreeEquipSlot(RPGEquipSlot* equipSlot)
{
	equipSlot->slots[RPGEquipSlot::HEAD] = 1;
	equipSlot->slots[RPGEquipSlot::EYE] = 2;
	equipSlot->slots[RPGEquipSlot::NECK] = 1;
	equipSlot->slots[RPGEquipSlot::CHEST] = 1;
	equipSlot->slots[RPGEquipSlot::BACK] = 1;
	equipSlot->slots[RPGEquipSlot::WRIST] = 2;
	equipSlot->slots[RPGEquipSlot::SHOULDER] = 2;
	equipSlot->slots[RPGEquipSlot::ELBOW] = 2;
	equipSlot->slots[RPGEquipSlot::ARM] = 2;
	equipSlot->slots[RPGEquipSlot::HAND] = 2;
	equipSlot->slots[RPGEquipSlot::FINGER] = 10;
	equipSlot->slots[RPGEquipSlot::WAIST] = 1;
	equipSlot->slots[RPGEquipSlot::LEG] = 2;
	equipSlot->slots[RPGEquipSlot::KNEE] = 2;
	equipSlot->slots[RPGEquipSlot::ANKLE] = 2;
	equipSlot->slots[RPGEquipSlot::FOOT] = 2;
	equipSlot->slots[RPGEquipSlot::TOE] = 10;
	equipSlot->slots[RPGEquipSlot::MISC] = 2;
}

int RPGRules::CheckForCritical(int value, bool& isCritical, bool& isFumbled) const
{
	int critRoll1 = RPGDice::Roll(D6);
	int critRoll2 = RPGDice::Roll(D6);
	isFumbled = critRoll1 == 1 && critRoll2 == 1;
	isCritical = !isFumbled && critRoll1 == critRoll2;
	if (isCritical)
		value *= 2;
	else if (isFumbled)
		value /= 2;
	return value;
}

void RPGRules::RandomizeAttributes(RPGCharacter* character)
{
	static const int NUM_DICE = 10;
	static const int MIN_TOTAL = 25;
	static const int MAX_TOTAL = 35;
	static const int MAX_REROLL = 10;

	int total = 0;
	for (int i = 0; i < MAX_REROLL; ++i)
	{
		total = RPGDice::Roll(NUM_DICE, D6);
		if (total >= MIN_TOTAL && total <= MAX_TOTAL)
			break;
	}

	TArray<FName> stats = GetPrimaryStats();
	while(total > 0)
	{
		RPGAttribute* attribute = character->GetAttribute(stats[FMath::RandRange(0, stats.Num() - 1)]);
		if (attribute->GetValue() >= attribute->GetMaxValue())
			continue;
		attribute->Increase(1);
		--total;
	}
}

RPGOccupation* RPGRules::GetMostSuitableOccupation(RPGCharacter* character, TArray<RPGOccupation*>& occupations) const
{
	TArray<FName> stats = GetPrimaryStats();
	TArray<TPair<int, RPGAttribute*>> attributes;
	attributes.AddDefaulted(stats.Num());
	for (int i = 0; i < stats.Num(); ++i)
		attributes[i].Value = character->GetAttribute(stats[i]);
	
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
			suitability += (stats.Num() - rank) * weight;
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

RPGTrait* RPGRules::FindTraitWithProperty(const TArray<RPGTrait*>& traits, FName propertyName) const
{
	for (auto trait : traits)
	{
		for (auto prop : trait->GetProperties())
		{
			if (prop.Key == propertyName)
				return trait;
		}
	}
	return nullptr;
}

bool RPGRules::HasTraitWithProperty(const TArray<RPGTrait*>& traits, FName propertyName) const
{
	return FindTraitWithProperty(traits, propertyName) != nullptr;
}
