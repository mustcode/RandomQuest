// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGItem
{
public:
	RPGItem(FName _name, FName _category, FName _type, FName _subtype, FName _equipSlot, FName _special, float _size, float _weight, int _damage, int _protection, int _durability, bool _isUnique, bool _isQuestItem);
	virtual ~RPGItem();

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

protected:
	FName name;
	FName category;
	FName type;
	FName subtype;
	FName equipSlot;
	FName special;
	float size;
	float weight;
	int damage;
	int protection;
	int durability;
	bool isUnique;
	bool isQuestItem;
};
