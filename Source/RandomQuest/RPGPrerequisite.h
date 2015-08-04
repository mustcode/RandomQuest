// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGPrerequisite
{
public:
	RPGPrerequisite();
	RPGPrerequisite(FName _name);
	~RPGPrerequisite();

	FName GetName() const;

	TArray<RPGTrait*> RequiredTraits;
	TArray<RPGTrait*> BannedTraits;
	TArray<TPair<FName, int>> MinimumStats;

protected:
	FName name;
};
