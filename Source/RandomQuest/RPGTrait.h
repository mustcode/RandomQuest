// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGTrait
{
public:

	struct Requirement
	{
		FName need;
		int amount;
		Requirement(FName _need, int _amount) : need(_need), amount(_amount){}
	};

	RPGTrait();
	RPGTrait(FName _name, int _value);
	~RPGTrait();

	FName GetName() const;
	int GetValue() const;

	void AddRequirement(FName need, int amount);
	int RequirementsCount() const;
	const Requirement& GetRequirement(int index) const;

protected:
	FName name;
	int value;
	TArray<Requirement> requirements;
};
