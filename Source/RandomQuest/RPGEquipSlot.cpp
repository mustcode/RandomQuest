// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGEquipSlot.h"

void RPGEquipSlot::Equip(const RPGEquipSlot& slot)
{
	ensure(CanEquip(slot));
	for (int i = 0; i < Slot::COUNT; ++i)
		slots[i] -= slot.slots[i];
}

void RPGEquipSlot::Unequip(const RPGEquipSlot& slot)
{
	for (int i = 0; i < Slot::COUNT; ++i)
		slots[i] += slot.slots[i];
}

bool RPGEquipSlot::CanEquip(const RPGEquipSlot& slot) const
{
	for (int i = 0; i < Slot::COUNT; ++i)
	{
		if (slots[i] < slot.slots[i])
			return false;
	}
	return true;
}
