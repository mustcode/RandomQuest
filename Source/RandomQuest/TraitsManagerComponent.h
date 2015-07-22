// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TraitsManagerComponent.generated.h"


USTRUCT(BlueprintType)
struct FTraitRequirement
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName need;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 amount;
};

USTRUCT(BlueprintType)
struct FTrait
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 value;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FTraitRequirement> requirements;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMQUEST_API UTraitsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTraitsManagerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FTrait> traits;
};
