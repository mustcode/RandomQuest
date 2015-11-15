// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGInventory.h"
#include "RPGItem.h"

RPGInventory::RPGInventory()
{
}

RPGInventory::~RPGInventory()
{
}

void RPGInventory::AddItem(RPGItem* item)
{
	ensure(!items.Contains(item));
	items.Add(item);
}

void RPGInventory::RemoveItem(RPGItem* item)
{
	ensure(items.Contains(item));
	items.Remove(item);
}

int RPGInventory::ItemsCount() const
{
	return items.Num();
}

RPGItem* RPGInventory::GetItem(int index) const
{
	ensure(index >= 0 && index < items.Num());
	return items[index];
}

RPGItem* RPGInventory::FindItem(FName name) const
{
	ensure(!name.IsNone() && name.IsValid());
	auto result = items.FindByPredicate([&](RPGItem* item){ return item->GetName() == name; });
	return *result;
}

const TArray<RPGItem*>& RPGInventory::GetItems() const
{
	return items;
}
