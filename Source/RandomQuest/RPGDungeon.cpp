// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGDungeon.h"

RPGDungeon::RPGDungeon(const FName& locationName, const FName& locationType, RPGLocation* parentLocation)
	: RPGLocation(locationName, locationType, parentLocation)
{
}

RPGDungeon::RPGDungeon() : RPGLocation()
{
}

RPGDungeon::~RPGDungeon()
{
}
