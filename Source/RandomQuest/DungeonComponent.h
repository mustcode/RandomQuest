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
	UDungeonComponent();

	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init(ULocationObject* location);
		
	ULocationObject* dungeon;
};
