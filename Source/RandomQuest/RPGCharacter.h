// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGAlignment.h"
#include "RPGAttribute.h"
#include "RPGTimer.h"

class RPGRace;
class RPGInventory;
class RPGWeapon;
class RPGAppearance;
class RPGSkill;
class RPGTrait;
class RPGAbnormality;

/**
 * 
 */
class RANDOMQUEST_API RPGCharacter
{
public:

	enum Gender
	{
		Male,
		Female
	};

	RPGCharacter();
	~RPGCharacter();
	
	RPGAttribute* AddAttribute(FName name, int minValue, int maxValue);
	RPGAttribute* GetAttribute(FName name);

	RPGTimer* AddTimer(FName name, float duration);
	RPGTimer* GetTimer(FName name);

	void AddSkill(RPGSkill* skill);
	bool HasSkill(RPGSkill* skill) const;
	bool HasSkill(FName name) const;
	RPGSkill* GetSkill(FName name) const;
	const TArray<RPGSkill*>& GetSkills() const;

	void AddTrait(RPGTrait* trait);
	bool HasTrait(RPGTrait* trait) const;
	bool HasTrait(FName name) const;
	RPGTrait* GetTrait(FName name) const;
	const TArray<RPGTrait*>& GetTraits() const;

	void SetActiveSkill(RPGSkill* skill);
	bool IsUsingSkill() const;
	void ClearActiveSkill();
	RPGSkill* GetActiveSkill() const;

	void DebugDump() const;

protected:

	FName title;
	FName firstName;
	FName middleName;
	FName lastName;
	
	Gender gender;
	RPGAppearance* appearance;
	RPGAlignment alignment;
	RPGInventory* inventory;
	
	TArray<RPGTrait*> traits;
	TArray<RPGSkill*> skills;
	TArray<RPGAbnormality*> abnormalities;

	TMap<FName, RPGAttribute> attributes;
	TMap<FName, RPGTimer> timers;

	RPGSkill* activeSkill;
};
