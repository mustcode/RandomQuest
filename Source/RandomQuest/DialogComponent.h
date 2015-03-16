// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"


USTRUCT(BlueprintType)
struct FDialogPhrase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FText text;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName speaker;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName expression;
};

USTRUCT(BlueprintType)
struct FDialogChoice
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FText description;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> requiredConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> addConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> removeConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName nextConversation;
};

USTRUCT(BlueprintType)
struct FConversation
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> triggerConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FDialogPhrase> phrases;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FDialogChoice> choices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool autoSelectFirstChoice;
};

USTRUCT(BlueprintType)
struct FTopic
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName topic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FConversation> conversations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool discussed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool repeatable;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RANDOMQUEST_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogComponent();

	virtual void InitializeComponent() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FTopic> topics;
};
