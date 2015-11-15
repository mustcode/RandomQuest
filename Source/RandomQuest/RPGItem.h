// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGItem
{
public:
	RPGItem(FName _name, FName _category, FName _type, FName _subtype, FName _equipSlot, float _size, float _weight, int _damage, int _protection, bool _isUnique, bool _isQuestItem);
	virtual ~RPGItem();

	FName GetName() const;
	FName GetCategory() const;
	FName GetType() const;
	FName GetSubType() const;
	FName GetEquipSlot() const;
	float GetSize() const;
	float GetWeight() const;
	int GetDamage() const;
	int GetProtection() const;
	bool IsUnique() const;
	bool IsQuestItem() const;

protected:
	FName name;
	FName category;
	FName type;
	FName subtype;
	FName equipSlot;
	float size;
	float weight;
	int damage;
	int protection;
	bool isUnique;
	bool isQuestItem;
};
