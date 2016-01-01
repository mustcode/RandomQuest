// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GameDataComponent.generated.h"

class RPGSkill;
class RPGTrait;
class RPGOccupation;
class RPGRace;
class RPGPrerequisite;
class RPGItem;
class RPGEquipSlot;
class UWorldDataInstance;


USTRUCT(BlueprintType)
struct FRequisite
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName need;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 value;

	FRequisite(){}
	FRequisite(FName _need, int32 _value)
		: need(_need)
		, value(_value){}
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
	FSkill(RPGSkill* skill, UWorldDataInstance* wdi);
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
	FTrait(RPGTrait* trait, UWorldDataInstance* wdi);
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

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FText displayName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FText description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName category;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName subtype;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName equipSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName special;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float size;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float weight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 protection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 durability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 value;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isUnique;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isQuestItem;

	FItem() {}
	FItem(RPGItem* item);
};

UENUM(BlueprintType)
enum class EItemSlot : uint8
{
	HEAD		UMETA(DisplayName = "Head"),
	EYE			UMETA(DisplayName = "Eye"),
	NECK		UMETA(DisplayName = "Neck"),
	CHEST		UMETA(DisplayName = "Chest"),
	BACK		UMETA(DisplayName = "Back"),
	WRIST		UMETA(DisplayName = "Wrist"),
	SHOULDER	UMETA(DisplayName = "Shoulder"),
	ELBOW		UMETA(DisplayName = "Elbow"),
	ARM			UMETA(DisplayName = "Arm"),
	HAND		UMETA(DisplayName = "Hand"),
	FINGER		UMETA(DisplayName = "Finger"),
	WAIST		UMETA(DisplayName = "Waist"),
	LEG			UMETA(DisplayName = "Leg"),
	KNEE		UMETA(DisplayName = "Knee"),
	ANKLE		UMETA(DisplayName = "Ankle"),
	FOOT		UMETA(DisplayName = "Foot"),
	TOE			UMETA(DisplayName = "Toe"),
	MISC		UMETA(DisplayName = "Misc")
};

USTRUCT(BlueprintType)
struct FRequireSlot
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	EItemSlot name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 count;
};

USTRUCT(BlueprintType)
struct FEquipSlot
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FRequireSlot> slots;
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FEquipSlot> equipSlots;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FItem> items;

private:
	RPGSkill* CreateSkill(const FSkill& skill);
	RPGTrait* CreateTrait(const FTrait& trait);
	RPGOccupation* CreateOccupation(const FOccupation& occupation);
	RPGRace* CreateRace(const FRace& race);
	RPGPrerequisite* CreatePrerequisite(FName name, const FPrerequisite& prerequisite);
	RPGEquipSlot* CreateEquipSlot(const FEquipSlot& equipSlot);
	RPGItem* CreateItem(const FItem& item);
};
