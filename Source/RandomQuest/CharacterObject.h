// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CharacterObject.generated.h"

class RPGCharacter;

/**
 * 
 */
UCLASS(BlueprintType)
class RANDOMQUEST_API UCharacterObject : public UObject
{
	GENERATED_BODY()
public:
	UCharacterObject();
	~UCharacterObject() override;
	
	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init();

	RPGCharacter* character;
};
