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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<UItemInstanceObject*> equipments;

	RPGCharacter character;
	RPGEquipSlot freeEquipSlots;
};
