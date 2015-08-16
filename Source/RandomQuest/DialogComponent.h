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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool triggerEvent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName eventId;
};

USTRUCT(BlueprintType)
struct FDialogChoice
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FText description;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName nextConversation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> requiredConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> bannedConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> addConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> removeConsequences;
};

USTRUCT(BlueprintType)
struct FConversation
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FDialogPhrase> phrases;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FDialogChoice> choices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool autoSelectFirstChoice;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool selectChoiceViaBlueprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> requiredConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> bannedConsequences;
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
	TArray<FName> requiredConsequences;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<FName> bannedConsequences;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RANDOMQUEST_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	UDialogComponent();

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool StartConversation(UWorldDataInstance* worldDataInstance);

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool SetCurrentConversation(FName conversationName);

	UFUNCTION(BlueprintCallable, Category = RPG)
	FConversation& GetCurrentConversation() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	FDialogPhrase& NextPhrase();

	UFUNCTION(BlueprintCallable, Category = RPG)
	FDialogPhrase& GetCurrentPhrase() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool IsLastPhrase() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool ShouldAutoSelectFirstChoice() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool ShouldSelectChoiceViaBlueprint() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool ShouldTriggerBlueprintEvent(FName& eventId) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	int32 GetNumberOfChoices() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	FDialogChoice& GetChoice(int32 index) const;

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
		for (auto consequence : subject.requiredConsequences)
		{
			if (!worldData->HasConsequence(consequence))
				return false;
		}
		for (auto consequence : subject.bannedConsequences)
		{
			if (worldData->HasConsequence(consequence))
				return false;
		}
		return true;
	}

	UWorldDataInstance* worldData;
	FTopic* currentTopic;
	FConversation* currentConversation;
	int currentPhrase;
};
