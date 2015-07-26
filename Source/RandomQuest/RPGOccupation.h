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

	void SetPrimaryStats(FName primary, FName secondary, FName tertiary);
	void GetPrimaryStats(FName& primary, FName& secondary, FName& tertiary) const;

	void AddTrait(RPGTrait* trait, bool essential);
	int TraitsCount(bool essential) const;
	const RPGTrait* GetTrait(int index, bool essential) const;

protected:
	FName name;
	FName primaryStat;
	FName secondaryStat;
	FName tertiaryStat;
	TArray<RPGTrait*> essentialTraits;
	TArray<RPGTrait*> optionalTraits;
};
