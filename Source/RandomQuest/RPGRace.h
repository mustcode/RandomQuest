// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGAlignment.h"

class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGRace
{
public:
	RPGRace(FName _name);
	~RPGRace();

	FName GetName() const;

	void AddTrait(RPGTrait* trait);
	int TraitsCount() const;
	RPGTrait* GetTrait(int index) const;

protected:
	FName name;
	TArray<RPGTrait*> traits;
};
