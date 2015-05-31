// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "DialogComponent.h"
#include "WorldDataInstance.h"

UDialogComponent::UDialogComponent() 
	: worldData(nullptr)
	, currentTopic(nullptr)
	, currentConversation(nullptr)
	, currentPhrase(0)
{
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
}

bool UDialogComponent::StartConversation(UWorldDataInstance* worldDataInstance)
{
	worldData = worldDataInstance;
	currentTopic = nullptr;
	currentConversation = nullptr;
	currentPhrase = 0;

	for (int i = 0; i < topics.Num(); ++i)
	{
		FTopic& topic = topics[i];
		if (!IsAvailable<FTopic>(topic))
			continue;
		currentTopic = &topics[i];
		break;
	}

	if (!currentTopic)
		return false;

	for (int i = 0; i < currentTopic->conversations.Num(); ++i)
	{
		FConversation& conversation = currentTopic->conversations[i];
		if (!IsAvailable<FConversation>(conversation))
			continue;
		currentConversation = &currentTopic->conversations[i];
		return true;
	}
	currentTopic = nullptr;
	return false;
}

bool UDialogComponent::SetCurrentConversation(FName conversationName)
{
	ensure(currentTopic);
	for (int i = 0; i < currentTopic->conversations.Num(); ++i)
	{
		FConversation& conversation = currentTopic->conversations[i];
		if (!IsAvailable<FConversation>(conversation) || (conversationName != conversation.name))
			continue;
		currentConversation = &currentTopic->conversations[i];
		currentPhrase = 0;
		return true;
	}
	return false;
}

FConversation& UDialogComponent::GetCurrentConversation() const
{
	return *currentConversation;
}

FDialogPhrase& UDialogComponent::NextPhrase()
{
	ensure(currentConversation);
	ensure(!IsLastPhrase());
	return currentConversation->phrases[++currentPhrase];
}

FDialogPhrase& UDialogComponent::GetCurrentPhrase() const
{
	ensure(currentConversation);
	return currentConversation->phrases[currentPhrase];
}

bool UDialogComponent::IsLastPhrase() const
{
	ensure(currentConversation);
	return currentPhrase == (currentConversation->phrases.Num() - 1);
}

bool UDialogComponent::ShouldAutoSelectFirstChoice() const
{
	ensure(currentConversation);
	return currentConversation->autoSelectFirstChoice;
}

bool UDialogComponent::ShouldSelectChoiceViaBlueprint() const
{
	ensure(currentConversation);
	return currentConversation->selectChoiceViaBlueprint;
}

bool UDialogComponent::ShouldTriggerBlueprintEvent(FName& eventId) const
{
	ensure(currentConversation);
	const FDialogPhrase& phrase = currentConversation->phrases[currentPhrase];
	eventId = phrase.eventId;
	return phrase.triggerEvent;
}

int32 UDialogComponent::GetNumberOfChoices() const
{
	ensure(currentConversation);
	int count = 0;
	for (auto choice : currentConversation->choices)
	{
		if (!IsAvailable<FDialogChoice>(choice))
			continue;
		++count;
	}
	return count;
}

FDialogChoice& UDialogComponent::GetChoice(int32 index) const
{
	ensure(currentConversation);
	ensure(index < currentConversation->choices.Num());
	int count = 0;
	TArray<FDialogChoice>& choices = currentConversation->choices;
	for (int i = 0; i < choices.Num(); ++i)
	{
		if (!IsAvailable<FDialogChoice>(choices[i]))
			continue;
		if (count == index)
			return choices[i];
		++count;
	}
	ensure(false);
	return choices[0];
}

FText UDialogComponent::GetChoiceText(int32 index) const
{
	return GetChoice(index).description;
}

bool UDialogComponent::MakeChoice(int32 index)
{
	ensure(currentConversation);
	ensure(index < currentConversation->choices.Num());
	int count = 0;
	FName nextConversation;
	for (auto choice : currentConversation->choices)
	{
		if (!IsAvailable<FDialogChoice>(choice))
			continue;
		if (count == index)
		{
			for (auto consequence : choice.addConsequences)
			{
				if (!worldData->HasConsequence(consequence))
					worldData->AddConsequence(consequence);
			}
			for (auto consequence : choice.removeConsequences)
			{
				if (worldData->HasConsequence(consequence))
					worldData->RemoveConsequence(consequence);
			}
			nextConversation = choice.nextConversation;
			break;
		}
		++count;
	}
	if (nextConversation.IsNone())
		return false;
	SetCurrentConversation(nextConversation);
	return true;
}
