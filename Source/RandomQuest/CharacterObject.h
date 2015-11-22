// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RPGCharacter.h"
#include "CharacterObject.generated.h"

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

	RPGCharacter character;
};
