// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGAttribute.h"
#include "RPGDice.h"

RPGAttribute::RPGAttribute()
{
}

RPGAttribute::~RPGAttribute()
{
}

void RPGAttribute::Randomize()
{
	value = FMath::RandRange(minValue, maxValue);
}
