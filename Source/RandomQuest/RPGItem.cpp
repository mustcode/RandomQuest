// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGItem.h"
#include "RPGTrait.h"

RPGItem::RPGItem(FText _displayName, FText _description, FName _name, FName _category, FName _type, FName _subtype, FName _equipSlot, float _size, float _weight, int _damage, int _protection, int _durability, int _value, bool _isUnique, bool _isQuestItem)
	: displayName(_displayName)
	, description(_description)
	, name(_name)
	, category(_category)
	, type(_type)
	, subtype(_subtype)
	, equipSlot(_equipSlot)
	, size(_size)
	, weight(_weight)
	, damage(_damage)
	, protection(_protection)
	, durability(_durability)
	, value(_value)
	, isUnique(_isUnique)
	, isQuestItem(_isQuestItem)
{
}

RPGItem::~RPGItem()
{
}

FText RPGItem::GetDisplayName() const
{
	return displayName;
}

FText RPGItem::GetDescription() const
{
	return description;
}

FName RPGItem::GetName() const
{
	return name;
}

FName RPGItem::GetCategory() const
{
	return category;
}

FName RPGItem::GetType() const
{
	return type;
}

FName RPGItem::GetSubType() const
{
	return subtype;
}

FName RPGItem::GetEquipSlot() const
{
	return equipSlot;
}

float RPGItem::GetSize() const
{
	return size;
}

float RPGItem::GetWeight() const
{
	return weight;
}

int RPGItem::GetDamage() const
{
	return damage;
}

int RPGItem::GetProtection() const
{
	return protection;
}

int RPGItem::GetDurability() const
{
	return durability;
}

int RPGItem::GetValue() const
{
	return value;
}

bool RPGItem::IsUnique() const
{
	return isUnique;
}

bool RPGItem::IsQuestItem() const
{
	return isQuestItem;
}

void RPGItem::AddTrait(RPGTrait* trait)
{
	ensure(!traits.Contains(trait));
	traits.Add(trait);
}

bool RPGItem::HasTrait(RPGTrait* trait) const
{
	ensure(trait != nullptr);
	return traits.Contains(trait);
}

bool RPGItem::HasTrait(FName name) const
{
	return traits.ContainsByPredicate([&](RPGTrait* trait) { return trait->GetName() == name; });
}

RPGTrait* RPGItem::GetTrait(FName name) const
{
	auto result = traits.FindByPredicate([&](RPGTrait* trait) { return trait->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

const TArray<RPGTrait*>& RPGItem::GetTraits() const
{
	return traits;
}
