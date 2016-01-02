// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RPGItemInstance.h"
#include "ItemInstanceObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RANDOMQUEST_API UItemInstanceObject : public UObject
{
	GENERATED_BODY()
public:
	UItemInstanceObject();
	~UItemInstanceObject() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	FName GetName() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetWear() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void ApplyWear(int32 amount);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void Repair();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool IsBroken() const;

	RPGItemInstance item;
};
