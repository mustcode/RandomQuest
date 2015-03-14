// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGLocation.h"

class RPGItem;
class RPGMonster;

/**
 * 
 */
class RANDOMQUEST_API RPGDungeon : public RPGLocation
{
public:
	RPGDungeon(const FName& locationName, const FName& locationType, RPGLocation* parentLocation);
	RPGDungeon();
	~RPGDungeon() override;

protected:
	TArray<RPGItem*> loots;
	TArray<RPGMonster*> monsters;
};
