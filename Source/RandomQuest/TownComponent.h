// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TownComponent.generated.h"

class ULocationObject;

UCLASS(ClassGroup = RPG, EditInlineNew, meta = (BlueprintSpawnableComponent))
class RANDOMQUEST_API UTownComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTownComponent();

	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init(ULocationObject* location);

	ULocationObject* town;
};
