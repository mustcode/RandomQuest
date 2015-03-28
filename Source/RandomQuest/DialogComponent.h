// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"


class UWorldDataInstance;

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
	TArray<FName> requiredConsequences;

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
	TArray<FName> requiredConsequences;

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

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool StartConversation(const UWorldDataInstance* worldDataInstance);

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool SetCurrentConversation(FName conversationName);

	UFUNCTION(BlueprintCallable, Category = RPG)
	FDialogPhrase NextPhrase();

	UFUNCTION(BlueprintCallable, Category = RPG)
	FDialogPhrase GetCurrentPhrase() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool IsLastPhrase() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool ShouldAutoSelectFirstChoice() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	int32 GetNumberOfChoices() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	FText GetChoiceText(int32 index) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool MakeChoice(int32 index);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FTopic> topics;

private:

	template <typename T>
	bool IsAvailable(const T& subject) const
	{
		ensure(worldData);
		bool canStart = true;
		for (auto consequence : subject.requiredConsequences)
		{
			if (worldData->HasConsequence(consequence))
				continue;
			canStart;
			break;
		}
		return canStart;
	}

	const UWorldDataInstance* worldData;
	FTopic* currentTopic;
	FConversation* currentConversation;
	int currentPhrase;
};
