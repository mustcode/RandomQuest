// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGItem.h"

RPGItem::RPGItem(FName _name, FName _category, FName _type, FName _subtype, FName _equipSlot, float _size, float _weight, int _damage, int _protection, bool _isUnique, bool _isQuestItem)
	: name(_name)
	, category(_category)
	, type(_type)
	, subtype(_subtype)
	, equipSlot(_equipSlot)
	, size(_size)
	, weight(_weight)
	, damage(_damage)
	, protection(_protection)
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

bool RPGItem::IsUnique() const
{
	return isUnique;
}

bool RPGItem::IsQuestItem() const
{
	return isQuestItem;
}
