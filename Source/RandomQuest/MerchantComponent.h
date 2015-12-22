// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "MerchantComponent.generated.h"


USTRUCT(BlueprintType)
struct FShopItem
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 quantity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 price;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> requiredConsequences;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMQUEST_API UMerchantComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMerchantComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FShopItem> merchandise;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float generosity;
};
