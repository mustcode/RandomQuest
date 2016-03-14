// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGTrait;
class RPGSkill;

/**
 * 
 */
class RANDOMQUEST_API RPGOccupation
{
public:
	RPGOccupation(FName _name);
	~RPGOccupation();

	FName GetName() const;

	void SetStatPreference(FName attribute, float weight);
	float GetStatPreference(FName attribute) const;

	void AddTrait(RPGTrait* trait, bool essential);
	const TArray<RPGTrait*>& GetEssentialTraits() const;
	const TArray<RPGTrait*>& GetOptionalTraits() const;

	void AddStartingSkill(RPGSkill* skill);
	const TArray<RPGSkill*>& GetStartingSkills() const;

protected:
	FName name;
	TMap<FName, float> statPreferences;
	TArray<RPGTrait*> essentialTraits;
	TArray<RPGTrait*> optionalTraits;
	TArray<RPGSkill*> startingSkills;
};
