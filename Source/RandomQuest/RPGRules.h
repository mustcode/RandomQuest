// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGCharacter;
class RPGSkill;
class RPGTrait;
class RPGRace;
class RPGOccupation;
class RPGPrerequisite;

/**
 * 
 */
class RANDOMQUEST_API RPGRules
{
public:
	RPGRules();
	~RPGRules();

	void RandomizeStats(RPGCharacter* character);
	void AssignRace(RPGCharacter* character, TArray<RPGRace*>& races);
	void AssignOccupation(RPGCharacter* character, TArray<RPGOccupation*>& occupations);
	void RandomizeCommonTraits(RPGCharacter* character, TArray<RPGTrait*>& traits);
	bool MeetPrerequisite(RPGCharacter* character, RPGPrerequisite* prerequisite) const;
	bool CanUseSkill(RPGCharacter* character, RPGSkill* skill) const;
	void DeductSkillCost(RPGCharacter* character, RPGSkill* skill);
	bool AbilityTest(RPGCharacter* character, FName ability, int difficulty, int& result) const;
	bool AbilityTest(RPGCharacter* character, FName ability, int difficulty) const;
	int ApplyHealing(RPGCharacter* healer, RPGCharacter* receiver, int amount, FName healingType, bool& isCritical);
	int ApplyDamage(RPGCharacter* instigator, RPGCharacter* victim, int amount, FName damageType, bool& isCritical);
	bool IsDead(RPGCharacter* character) const;

private:
	void RandomizeAttributes(RPGCharacter* character);
	RPGOccupation* GetMostSuitableOccupation(RPGCharacter* character, TArray<RPGOccupation*>& occupations) const;
};
