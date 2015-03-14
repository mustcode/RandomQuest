// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "RandomQuestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMQUEST_API ARandomQuestGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
};
