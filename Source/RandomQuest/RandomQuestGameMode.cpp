// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RandomQuestGameMode.h"
#include "RPGRules.h"
#include "RPGCharacter.h"

void ARandomQuestGameMode::StartPlay()
{
	Super::StartPlay();

	UE_LOG(LogTemp, Warning, TEXT("Start tests..."));
	RPGRules rules;
	rules.GenerateParty(3);
	auto party = rules.GetParty();
	for (auto character : party)
		character->DebugDump();
	UE_LOG(LogTemp, Warning, TEXT("Tests completed..."));
}
