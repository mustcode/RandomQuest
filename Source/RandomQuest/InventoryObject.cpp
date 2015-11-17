// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "InventoryObject.h"
#include "RPGInventory.h"
#include "RPGItem.h"

UInventoryObject::UInventoryObject()
	: inventory(nullptr)
	, gold(0)
{
}

UInventoryObject::~UInventoryObject()
{
	if (inventory)
		delete inventory;
}

void UInventoryObject::Init()
{
	inventory = new RPGInventory;
}

void UInventoryObject::AddItem(const FItem& item)
{
	ensure(inventory != nullptr);
	RPGItem* rpgItem = CreateItem(item);
	inventory->AddItem(rpgItem);
}

void UInventoryObject::RemoveItem(const FItem & item)
{
	ensure(inventory != nullptr);
	RPGItem* rpgItem = inventory->FindItem(item.name);
	inventory->RemoveItem(rpgItem);
}

int32 UInventoryObject::ItemsCount() const
{
	ensure(inventory != nullptr);
	return inventory->ItemsCount();
}

FItem UInventoryObject::GetItem(int32 index) const
{
	ensure(inventory != nullptr);
	RPGItem* rpgItem = inventory->GetItem(index);
	return FItem(rpgItem);
}

TArray<FItem> UInventoryObject::GetItems() const
{
	ensure(inventory != nullptr);
	TArray<FItem> items;
	TArray<RPGItem*> rpgItems = inventory->GetItems();
	for (auto item : rpgItems)
		items.Add(FItem(item));
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

RPGItem* UInventoryObject::CreateItem(const FItem& item)
{
	RPGItem* rpgItem = new RPGItem(item.name, item.category, item.type, item.subtype, item.equipSlot, item.special, item.size, item.weight, item.damage, item.protection, item.isUnique, item.isQuestItem);
	return rpgItem;
}

FItem::FItem(RPGItem* item)
{
	name = item->GetName();
	category = item->GetCategory();
	type = item->GetType();
	subtype = item->GetSubType();
	equipSlot = item->GetEquipSlot();
	special = item->GetSpecial();
	size = item->GetSize();
	weight = item->GetWeight();
	damage = item->GetDamage();
	protection = item->GetProtection();
	isUnique = item->IsUnique();
	isQuestItem = item->IsQuestItem();
}