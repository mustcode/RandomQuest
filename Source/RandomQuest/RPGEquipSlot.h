// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGEquipSlot
{
public:

	enum Slot
	{
		HEAD = 0,
		EYE,
		NECK,
		CHEST,
		BACK,
		WRIST,
		SHOULDER,
		ELBOW,
		ARM,
		HAND,
		FINGER,
		WAIST,
		LEG,
		KNEE,
		ANKLE,
		FOOT,
		TOE,
		MISC,
		COUNT
	};

	void Equip(const RPGEquipSlot& slot);
	void Unequip(const RPGEquipSlot& slot);
	bool CanEquip(const RPGEquipSlot& slot) const;
	bool IsEquippable() const;
	void Clear();

	FName name;
	int slots[Slot::COUNT];
};
