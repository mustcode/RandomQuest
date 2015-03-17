// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "DialogComponent.h"
#include "WorldDataInstance.h"

UDialogComponent::UDialogComponent() : currentTopic(nullptr)
{
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
}

bool UDialogComponent::StartConversation(const UWorldDataInstance* worldDataInstance)
{
	currentTopic = nullptr;
	currentConversation = nullptr;

	for (int i = 0; i < topics.Num(); ++i)
	{
		FTopic& topic = topics[i];
		if (topic.discussed)
			continue;
		if (!CanStartTopic(worldDataInstance, topic))
			continue;
		currentTopic = &topics[i];
		break;
	}

	if (!currentTopic)
	{
		for (int i = 0; i < topics.Num(); ++i)
		{
			FTopic& topic = topics[i];
			if (!topic.discussed || !topic.repeatable)
				continue;
			if (!CanStartTopic(worldDataInstance, topic))
				continue;
			currentTopic = &topics[i];
			break;
		}
	}
	if (!currentTopic)
		return false;

	for (int i = 0; i < currentTopic->conversations.Num(); ++i)
	{
		FConversation& conversation = currentTopic->conversations[i];
		if (!CanStartConversation(worldDataInstance, conversation))
			continue;
		currentConversation = &currentTopic->conversations[i];
		return true;
	}
	currentTopic = nullptr;
	return false;
}

bool UDialogComponent::CanStartTopic(const UWorldDataInstance* worldDataInstance, const FTopic& topic) const
{
	bool canStart = true;
	for (auto consequence : topic.requiredConsequences)
	{
		if (worldDataInstance->HasConsequence(consequence))
			continue;
		canStart = false;
		break;
	}
	return canStart;
}

bool UDialogComponent::CanStartConversation(const UWorldDataInstance* worldDataInstance, const FConversation& conversation) const
{
	bool canStart = true;
	for (auto consequence : conversation.requiredConsequences)
	{
		if (worldDataInstance->HasConsequence(consequence))
			continue;
		canStart;
		break;
	}
	return canStart;
}
