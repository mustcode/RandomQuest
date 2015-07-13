// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "TownComponent.h"

UTownComponent::UTownComponent()
{
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
}
