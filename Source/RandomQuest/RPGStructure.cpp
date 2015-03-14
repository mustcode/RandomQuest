// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGStructure.h"

RPGStructure::RPGStructure(const FName& structureName, const FName& structureType, RPGLocation* parentLocation)
	: RPGLocation(structureName, structureType, parentLocation)
{
}

RPGStructure::RPGStructure() : RPGLocation()
{
}

RPGStructure::~RPGStructure()
{
}
