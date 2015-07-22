// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGCharacter;
class RPGSkill;

/**
 * 
 */
class RANDOMQUEST_API RPGRules
{
public:
	RPGRules();
	~RPGRules();

	void RandomizeStats(RPGCharacter* character);
	bool AbilityTest(RPGCharacter* character, FName ability, int difficulty, int& result);
	bool AbilityTest(RPGCharacter* character, FName ability, int difficulty);
	bool TryLearnSkill(RPGCharacter* character, RPGSkill* skill);

private:
	void RandomizeAttributes(RPGCharacter* character);
	bool HasSkillRequirement(RPGCharacter* character, FName requirement, int amount) const;
};
