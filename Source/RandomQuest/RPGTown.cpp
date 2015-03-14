// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGTown.h"

RPGTown::RPGTown(const FName& locationName, const FName& locationType, RPGLocation* parentLocation)
	: RPGLocation(locationName, locationType, parentLocation)
{
}

RPGTown::RPGTown() : RPGLocation()
{
}

RPGTown::~RPGTown()
{
}
