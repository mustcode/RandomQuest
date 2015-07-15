// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SkillsManagerComponent.generated.h"


USTRUCT(BlueprintType)
struct FSkillCommand
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName command;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float value;
};

USTRUCT(BlueprintType)
struct FSkillRequirement
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
		FName need;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
		int32 amount;
};

USTRUCT(BlueprintType)
struct FSkillCost
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName resource;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 amount;
};

USTRUCT(BlueprintType)
struct FSkill
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName variationOf;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkillCommand> commands;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkillRequirement> requirements;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkillCost> costs;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMQUEST_API USkillsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillsManagerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkill> skills;
};
