// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DungeonComponent.generated.h"

UCLASS(ClassGroup = (Custom), EditInlineNew, meta = (BlueprintSpawnableComponent))
class RANDOMQUEST_API UDungeonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDungeonComponent();
};
