// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "MerchantComponent.h"


// Sets default values for this component's properties
UMerchantComponent::UMerchantComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UMerchantComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
