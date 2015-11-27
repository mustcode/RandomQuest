// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RPGCharacter.h"
#include "RPGEquipSlot.h"
#include "CharacterObject.generated.h"

class UItemInstanceObject;

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
	TArray<UItemInstanceObject*> equipments;
	RPGEquipSlot freeEquipSlots;
};
