// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "SkillsManagerComponent.h"
#include "WorldDataInstance.h"

// Sets default values for this component's properties
USkillsManagerComponent::USkillsManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USkillsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);
	for (const FSkill& skill : skills)
		wdi->AddSkill(skill);
}
