// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "InventoryObject.h"
#include "ItemInstanceObject.h"

UInventoryObject::UInventoryObject() 
	: gold(0)
	, maxSpace(0)
	, maxWeight(0)
{
}

UInventoryObject::~UInventoryObject()
{
}

void UInventoryObject::AddItem(UItemInstanceObject* item)
{
	ensure(!HasItem(item));
	items.Add(item);
}

void UInventoryObject::RemoveItem(UItemInstanceObject* item)
{
	ensure(HasItem(item));
	items.Remove(item);
}

bool UInventoryObject::HasItem(UItemInstanceObject* item)
{
	ensure(item != nullptr);
	ensure(!item->item.GetName().IsNone() && item->item.GetName().IsValid());
	return items.Contains(item);
}

TArray<UItemInstanceObject*>& UInventoryObject::GetItems()
{
	return items;
}

void UInventoryObject::AddGold(int32 amount)
{
	gold += amount;
}

void UInventoryObject::SubtractGold(int32 amount)
{
	gold -= amount;
}

int32 UInventoryObject::GetGold(int32 amount) const
{
	return gold;
}
