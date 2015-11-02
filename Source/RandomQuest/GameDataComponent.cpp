// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "GameDataComponent.h"
#include "WorldDataInstance.h"
#include "RPGSkill.h"
#include "RPGTrait.h"
#include "RPGOccupation.h"
#include "RPGRace.h"
#include "RPGPrerequisite.h"


// Sets default values for this component's properties
UGameDataComponent::UGameDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGameDataComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGameDataComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	for (const FSkill& skill : skills)
		wdi->AddSkill(CreateSkill(skill));
	for (const FTrait& trait : traits)
		wdi->AddTrait(CreateTrait(trait));

	for (const FSkill& skill : skills)
		wdi->AddPrerequisite(CreatePrerequisite(skill.name, skill.prerequisite));
	for (const FTrait& trait : traits)
		wdi->AddPrerequisite(CreatePrerequisite(trait.name, trait.prerequisite));

	for (const FOccupation& occupation : occupations)
		wdi->AddOccupation(CreateOccupation(occupation));
	for (const FRace& race : races)
		wdi->AddRace(CreateRace(race));
}

RPGSkill* UGameDataComponent::CreateSkill(const FSkill& skill)
{
	RPGSkill* rpgSkill = new RPGSkill(skill.name, skill.variationOf, skill.isUsableInCombat, skill.isUsableOutOfCombat, skill.canSelectTargetAlly, skill.canSelectTargetEnemy);
	for (auto cmd : skill.commands)
		rpgSkill->AddCommand(cmd.command, cmd.time, cmd.value);
	for (auto cost : skill.costs)
		rpgSkill->AddCost(cost.resource, cost.amount);
	return rpgSkill;
}

RPGTrait* UGameDataComponent::CreateTrait(const FTrait& trait)
{
	RPGTrait* rpgTrait = new RPGTrait(trait.name);
	for (auto traitProperty : trait.properties)
		rpgTrait->SetProperty(traitProperty.name, traitProperty.value);
	return rpgTrait;
}

RPGOccupation* UGameDataComponent::CreateOccupation(const FOccupation& occupation)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGOccupation* rpgOccupation = new RPGOccupation(occupation.name);
	for (auto pref : occupation.statPreferences)
		rpgOccupation->SetStatPreference(pref.attribute, pref.weight);
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

RPGPrerequisite* UGameDataComponent::CreatePrerequisite(FName name, const FPrerequisite& prerequisite)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGPrerequisite* rpgPrerequisite = new RPGPrerequisite(name);
	for (auto trait : prerequisite.requiredTraits)
		rpgPrerequisite->RequiredTraits.Add(wdi->GetTrait(trait));
	for (auto trait : prerequisite.bannedTraits)
		rpgPrerequisite->BannedTraits.Add(wdi->GetTrait(trait));
	for (auto requisite : prerequisite.minimumStats)
	{
		TPair<FName, int> item;
		item.Key = requisite.need;
		item.Value = requisite.value;
		rpgPrerequisite->MinimumStats.Add(item);
	}
	return rpgPrerequisite;
}

FSkill::FSkill(RPGSkill* skill, UWorldDataInstance* wdi)
{
	name = skill->GetName();
	variationOf = skill->GetVariationOf();
	isUsableInCombat = skill->IsUsableInCombat();
	isUsableOutOfCombat = skill->IsUsableOutOfCombat();
	canSelectTargetAlly = skill->CanSelectTargetAlly();
	canSelectTargetEnemy = skill->CanSelectTargetEnemy();
	for (auto cmd : skill->GetCommands())
		commands.Add(FSkillCommand(cmd.command, cmd.time, cmd.value));
	for (auto cost : skill->GetCosts())
		costs.Add(FSkillCost(cost.Key, cost.Value));
	ensure(wdi != nullptr);
	wdi->GetPrerequisite(name, prerequisite);
}

FTrait::FTrait(RPGTrait* trait, UWorldDataInstance* wdi)
{
	name = trait->GetName();
	for (auto prop : trait->GetProperties())
		properties.Add(FTraitProperty(prop.Key, prop.Value));
	ensure(wdi != nullptr);
	wdi->GetPrerequisite(name, prerequisite);
}
