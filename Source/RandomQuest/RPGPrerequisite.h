// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	TArray<TPair<FName, int>> RequiredTraits;
	TArray<TPair<FName, int>> BannedTraits;
	TArray<TPair<FName, int>> MinimumStats;

protected:
	FName name;
};
