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

FName RPGItemInstance::GetName() const
{
	return item->GetName();
}

FName RPGItemInstance::GetEquipSlot() const
{
	return item->GetEquipSlot();
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

bool RPGItemInstance::IsValid() const
{
	return (item != nullptr) && !item->GetName().IsNone() && item->GetName().IsValid();
}
