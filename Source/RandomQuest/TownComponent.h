// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TownComponent.generated.h"

UCLASS(ClassGroup = RPG, EditInlineNew, meta = (BlueprintSpawnableComponent))
class RANDOMQUEST_API UTownComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTownComponent();
};
