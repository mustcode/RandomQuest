// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "DungeonComponent.h"

UDungeonComponent::UDungeonComponent()
{
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
}
