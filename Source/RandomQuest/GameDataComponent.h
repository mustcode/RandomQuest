// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GameDataComponent.generated.h"

class RPGSkill;
class RPGTrait;
class RPGOccupation;
class RPGRace;
class RPGPrerequisite;


USTRUCT(BlueprintType)
struct FRequisite
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName need;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 value;
};

USTRUCT(BlueprintType)
struct FPrerequisite
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> requiredTraits;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> bannedTraits;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FRequisite> minimumStats;
};

USTRUCT(BlueprintType)
struct FSkillCommand
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName command;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float time;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float value;

	FSkillCommand(){}
	FSkillCommand(FName _command, float _time, float _value)
		: command(_command)
		, time(_time)
		, value(_value){}
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

	FSkillCost(){}
	FSkillCost(FName _resource, int32 _amount)
		: resource(_resource)
		, amount(_amount){}
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
	bool isUsableInCombat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isUsableOutOfCombat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool canSelectTargetAlly;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool canSelectTargetEnemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkillCommand> commands;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FSkillCost> costs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FPrerequisite prerequisite;

	FSkill(){}
	FSkill(RPGSkill* skill);
};

USTRUCT(BlueprintType)
struct FTraitProperty
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 value;

	FTraitProperty(){}
	FTraitProperty(FName _name, int32 _value)
		: name(_name)
		, value(_value){}
};

USTRUCT(BlueprintType)
struct FTrait
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FTraitProperty> properties;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FPrerequisite prerequisite;

	FTrait(){}
	FTrait(RPGTrait* trait);
};

USTRUCT(BlueprintType)
struct FStatPreference
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName attribute;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float weight;
};

USTRUCT(BlueprintType)
struct FOccupation
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FStatPreference> statPreferences;

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
	virtual void InitializeComponent() override;

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
	RPGPrerequisite* CreatePrerequisite(FName name, const FPrerequisite& prerequisite);
};
