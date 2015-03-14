// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGAttributes.h"
#include "RPGAlignment.h"

class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGRace
{
public:
	RPGRace();
	~RPGRace();
	const int* GetStatBonus() const { return statsBonus; }

protected:
	FName name;
	float sizeMin;
	float sizeMax;
	int speed;
	int matureAge;
	int oldAge;
	int maxAge;
	int statsBonus[RPGAttributes::Stat::Count];
	TArray<RPGAlignment> alignments;
	TArray<FName> languages;
	TArray<RPGTrait*> traits;
	RPGRace* subrace;
};
