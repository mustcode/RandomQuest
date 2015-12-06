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

void UInventoryObject::SetName(FName _name)
{
	name = _name;
}

FName UInventoryObject::GetName() const
{
	return name;
}

void UInventoryObject::SetCapacity(float space, float weight)
{
	maxSpace = space;
	maxWeight = weight;
}

void UInventoryObject::AddItem(UItemInstanceObject* item)
{
	ensure(!HasItem(item));
	ensure(HasEnoughSpace(item) && NotTooHeavy(item));
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

float UInventoryObject::GetAvailableSpace() const
{
	int totalSize = 0;
	for (auto item : items)
		totalSize += item->item.GetSize();
	return maxSpace - totalSize;
}

float UInventoryObject::GetAvailableWeight() const
{
	int totalWeight = 0;
	for (auto item : items)
		totalWeight += item->item.GetWeight();
	return maxWeight - totalWeight;
}

bool UInventoryObject::HasEnoughSpace(const UItemInstanceObject* item) const
{
	return GetAvailableSpace() >= item->item.GetSize();
}

bool UInventoryObject::NotTooHeavy(const UItemInstanceObject* item) const
{
	return GetAvailableWeight() >= item->item.GetWeight();
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
