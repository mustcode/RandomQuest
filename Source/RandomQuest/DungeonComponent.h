// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DungeonComponent.generated.h"

class ULocationObject;

UCLASS(ClassGroup = (Custom), EditInlineNew, meta = (BlueprintSpawnableComponent))
class RANDOMQUEST_API UDungeonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDungeonComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init(ULocationObject* location);
		
	ULocationObject* dungeon;
};
