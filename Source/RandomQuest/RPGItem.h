// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGItem
{
public:
	RPGItem(FText _displayName, FText _description, FName _name, FName _category, FName _type, FName _subtype, FName _equipSlot, float _size, float _weight, int _damage, int _protection, int _durability, int _value, bool _isUnique, bool _isQuestItem);
	virtual ~RPGItem();

	FText GetDisplayName() const;
	FText GetDescription() const;
	FName GetName() const;
	FName GetCategory() const;
	FName GetType() const;
	FName GetSubType() const;
	FName GetEquipSlot() const;
	float GetSize() const;
	float GetWeight() const;
	int GetDamage() const;
	int GetProtection() const;
	int GetDurability() const;
	int GetValue() const;
	bool IsUnique() const;
	bool IsQuestItem() const;

	void AddTrait(RPGTrait* trait);
	bool HasTrait(RPGTrait* trait) const;
	bool HasTrait(FName name) const;
	RPGTrait* GetTrait(FName name) const;
	const TArray<RPGTrait*>& GetTraits() const;

protected:
	FText displayName;
	FText description;
	FName name;
	FName category;
	FName type;
	FName subtype;
	FName equipSlot;
	float size;
	float weight;
	int damage;
	int protection;
	int durability;
	int value;
	bool isUnique;
	bool isQuestItem;
	TArray<RPGTrait*> traits;
};
