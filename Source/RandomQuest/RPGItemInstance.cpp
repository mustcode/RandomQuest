// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGItemInstance.h"
#include "RPGItem.h"

RPGItemInstance::RPGItemInstance()
	:item(nullptr)
	,wear(0)
{
}

RPGItemInstance::RPGItemInstance(RPGItem* _item)
	: item(_item)
	, wear(_item->GetDurability())
{
}

RPGItemInstance::~RPGItemInstance()
{
}

void RPGItemInstance::SetItem(RPGItem* _item)
{
	item = _item;
	wear = _item->GetDurability();
}

RPGItem* RPGItemInstance::GetItem() const
{
	return item;
}

int RPGItemInstance::GetWear() const
{
	return wear;
}

void RPGItemInstance::ApplyWear(int amount)
{
	ensure(wear > 0);
	wear -= amount;
}

void RPGItemInstance::Repair()
{
	wear = item->GetDurability();
}

bool RPGItemInstance::IsBroken() const
{
	return wear <= 0;
}

FName RPGItemInstance::GetName() const
{
	return item->GetName();
}

FName RPGItemInstance::GetCategory() const
{
	return item->GetCategory();
}

FName RPGItemInstance::GetType() const
{
	return item->GetType();
}

FName RPGItemInstance::GetSubType() const
{
	return item->GetSubType();
}

FName RPGItemInstance::GetEquipSlot() const
{
	return item->GetEquipSlot();
}

FName RPGItemInstance::GetSpecial() const
{
	return item->GetSpecial();
}

float RPGItemInstance::GetSize() const
{
	return item->GetSize();
}

float RPGItemInstance::GetWeight() const
{
	return item->GetWeight();
}

int RPGItemInstance::GetDamage() const
{
	return item->GetDamage();
}

int RPGItemInstance::GetProtection() const
{
	return item->GetProtection();
}

int RPGItemInstance::GetDurability() const
{
	return item->GetDurability();
}

bool RPGItemInstance::IsUnique() const
{
	return item->IsUnique();
}

bool RPGItemInstance::IsQuestItem() const
{
	return item->IsQuestItem();
}

bool RPGItemInstance::IsValid() const
{
	return (item != nullptr) && !item->GetName().IsNone() && item->GetName().IsValid();
}
