// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGItem.h"
#include "RPGTrait.h"
#include "RPGSkill.h"

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
	ensure(trait != nullptr);
	ensure(!traits.Contains(trait));
	traits.Add(trait);
}

bool RPGItem::HasTrait(RPGTrait* trait) const
{
	ensure(trait != nullptr);
	return traits.Contains(trait);
}

bool RPGItem::HasTrait(FName traitName) const
{
	return traits.ContainsByPredicate([&](RPGTrait* trait) { return trait->GetName() == traitName; });
}

RPGTrait* RPGItem::GetTrait(FName traitName) const
{
	auto result = traits.FindByPredicate([&](RPGTrait* trait) { return trait->GetName() == traitName; });
	return (result != nullptr) ? *result : nullptr;
}

const TArray<RPGTrait*>& RPGItem::GetTraits() const
{
	return traits;
}

void RPGItem::AddSkill(RPGSkill* skill)
{
	ensure(skill != nullptr);
	ensure(!skills.Contains(skill));
	skills.Add(skill);
}

bool RPGItem::HasSkill(RPGSkill* skill) const
{
	ensure(skill != nullptr);
	return skills.Contains(skill);
}

bool RPGItem::HasSkill(FName skillName) const
{
	return skills.ContainsByPredicate([&](RPGSkill* skill) { return skill->GetName() == skillName; });
}

RPGSkill* RPGItem::GetSkill(FName skillName) const
{
	auto result = skills.FindByPredicate([&](RPGSkill* skill) { return skill->GetName() == skillName; });
	return (result != nullptr) ? *result : nullptr;
}

const TArray<RPGSkill*>& RPGItem::GetSkills() const
{
	return skills;
}
