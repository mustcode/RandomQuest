// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "DungeonComponent.h"
#include "LocationObject.h"

UDungeonComponent::UDungeonComponent() : dungeon(nullptr)
{
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UDungeonComponent::Init(ULocationObject* location)
{
	dungeon = location;
}
