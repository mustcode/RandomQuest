// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "DialogComponent.h"

UDialogComponent::UDialogComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogComponent::InitializeComponent()
{
	Super::InitializeComponent();
}
