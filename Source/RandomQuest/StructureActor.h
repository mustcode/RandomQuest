// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StructureActor.generated.h"

class ULocationObject;

/**
 * 
 */
UCLASS(ClassGroup = RPG)
class RANDOMQUEST_API AStructureActor : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init(ULocationObject* location);

	ULocationObject* structure;
};
