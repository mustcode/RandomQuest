// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "TownComponent.h"
#include "LocationObject.h"

UTownComponent::UTownComponent() : town(nullptr)
{
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTownComponent::Init(ULocationObject* location)
{
	town = location;
}


