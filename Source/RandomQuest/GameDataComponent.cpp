// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "GameDataComponent.h"
#include "WorldDataInstance.h"
#include "RPGSkill.h"
#include "RPGTrait.h"
#include "RPGOccupation.h"
#include "RPGRace.h"


// Sets default values for this component's properties
UGameDataComponent::UGameDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGameDataComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);
	for (const FSkill& skill : skills)
		wdi->AddSkill(CreateSkill(skill));
	for (const FTrait& trait : traits)
		wdi->AddTrait(CreateTrait(trait));
	for (const FOccupation& occupation : occupations)
		wdi->AddOccupation(CreateOccupation(occupation));
	for (const FRace& race : races)
		wdi->AddRace(CreateRace(race));
}

RPGSkill* UGameDataComponent::CreateSkill(const FSkill& skill)
{
	RPGSkill* rpgSkill = new RPGSkill;
	rpgSkill->SetName(skill.name);
	rpgSkill->SetVariationOf(skill.variationOf);
	for (auto cmd : skill.commands)
		rpgSkill->AddCommand(cmd.command, cmd.value);
	for (auto cost : skill.costs)
		rpgSkill->AddCost(cost.resource, cost.amount);
	for (auto req : skill.requirements)
		rpgSkill->AddRequirement(req.need, req.amount);
	return rpgSkill;
}

RPGTrait* UGameDataComponent::CreateTrait(const FTrait& trait)
{
	RPGTrait* rpgTrait = new RPGTrait(trait.name, trait.value);
	for (auto req : trait.requirements)
		rpgTrait->AddRequirement(req.need, req.amount);
	return rpgTrait;
}

RPGOccupation* UGameDataComponent::CreateOccupation(const FOccupation& occupation)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGOccupation* rpgOccupation = new RPGOccupation(occupation.name);
	rpgOccupation->SetPrimaryStats(occupation.primaryStat, occupation.secondaryStat, occupation.tertiaryStat);
	for (auto trait : occupation.essentialTraits)
		rpgOccupation->AddTrait(wdi->GetTrait(trait), true);
	for (auto trait : occupation.optionalTraits)
		rpgOccupation->AddTrait(wdi->GetTrait(trait), false);
	return rpgOccupation;
}

RPGRace* UGameDataComponent::CreateRace(const FRace& race)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGRace* rpgRace = new RPGRace(race.name);
	for (auto trait : race.traits)
		rpgRace->AddTrait(wdi->GetTrait(trait));
	return rpgRace;
}
