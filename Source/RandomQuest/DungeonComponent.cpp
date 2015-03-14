// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "DungeonComponent.h"
#include "LocationObject.h"

// Sets default values for this component's properties
UDungeonComponent::UDungeonComponent() : dungeon(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDungeonComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UDungeonComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UDungeonComponent::Init(ULocationObject* location)
{
	dungeon = location;
}
