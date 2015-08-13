// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGTrait;

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
	int TraitsCount(bool essential) const;
	RPGTrait* GetTrait(int index, bool essential) const;

protected:
	FName name;
	TMap<FName, float> statPreferences;
	TArray<RPGTrait*> essentialTraits;
	TArray<RPGTrait*> optionalTraits;
};
