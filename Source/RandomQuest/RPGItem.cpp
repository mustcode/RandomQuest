// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGItem.h"

RPGItem::RPGItem(FName _name, FName _category, FName _type, FName _subtype, FName _equipSlot, FName _special, float _size, float _weight, int _damage, int _protection, int _durability, bool _isUnique, bool _isQuestItem)
	: name(_name)
	, category(_category)
	, type(_type)
	, subtype(_subtype)
	, equipSlot(_equipSlot)
	, special(_special)
	, size(_size)
	, weight(_weight)
	, damage(_damage)
	, protection(_protection)
	, durability(_durability)
	, isUnique(_isUnique)
	, isQuestItem(_isQuestItem)
{
}

RPGItem::~RPGItem()
{
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

FName RPGItem::GetSpecial() const
{
	return special;
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

bool RPGItem::IsUnique() const
{
	return isUnique;
}

bool RPGItem::IsQuestItem() const
{
	return isQuestItem;
}
