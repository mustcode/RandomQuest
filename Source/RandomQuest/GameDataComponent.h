// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GameDataComponent.generated.h"

class RPGSkill;
class RPGTrait;
class RPGOccupation;
class RPGRace;


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
struct FPrerequisite
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
	TArray<FSkillCost> costs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FPrerequisite> prerequisites;
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
	TArray<FPrerequisite> prerequisites;
};

USTRUCT(BlueprintType)
struct FOccupation
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName primaryStat;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName secondaryStat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName tertiaryStat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> essentialTraits;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> optionalTraits;
};

USTRUCT(BlueprintType)
struct FRace
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> traits;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMQUEST_API UGameDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameDataComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkill> skills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FTrait> traits;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FOccupation> occupations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FRace> races;

private:
	RPGSkill* CreateSkill(const FSkill& skill);
	RPGTrait* CreateTrait(const FTrait& trait);
	RPGOccupation* CreateOccupation(const FOccupation& occupation);
	RPGRace* CreateRace(const FRace& race);
};
