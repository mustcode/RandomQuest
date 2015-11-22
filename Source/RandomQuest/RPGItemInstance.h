// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGItem;

/**
 * 
 */
class RANDOMQUEST_API RPGItemInstance
{
public:
	RPGItemInstance();
	RPGItemInstance(RPGItem* _item);
	virtual ~RPGItemInstance();

	RPGItem* GetItem() const;
	int GetWear() const;
	void ApplyWear(int amount);
	void Repair();
	bool IsBroken() const;

	FName GetName() const;
	FName GetCategory() const;
	FName GetType() const;
	FName GetSubType() const;
	FName GetEquipSlot() const;
	FName GetSpecial() const;
	float GetSize() const;
	float GetWeight() const;
	int GetDamage() const;
	int GetProtection() const;
	int GetDurability() const;
	bool IsUnique() const;
	bool IsQuestItem() const;

	bool IsValid() const;

protected:
	RPGItem* item;
	int wear;
};
