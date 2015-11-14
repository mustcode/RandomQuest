// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "InventoryObject.generated.h"

class RPGInventory;


USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName equipSlot;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RANDOMQUEST_API UInventoryObject : public UObject
{
	GENERATED_BODY()
public:
	UInventoryObject();
	~UInventoryObject() override;
	
	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init();

	RPGInventory* inventory;

private:
	int32 gold, silver, copper;
};
