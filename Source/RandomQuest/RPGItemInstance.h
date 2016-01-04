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

	FName GetName() const;
	FName GetEquipSlot() const;

	void SetItem(RPGItem* _item);
	RPGItem* GetItem() const;
	int GetWear() const;
	void ApplyWear(int amount);
	void Repair();
	bool IsBroken() const;
	bool IsValid() const;

protected:
	RPGItem* item;
	int wear;
};
