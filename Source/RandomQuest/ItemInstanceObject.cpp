// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "ItemInstanceObject.h"

UItemInstanceObject::UItemInstanceObject()
{
}

UItemInstanceObject::~UItemInstanceObject()
{
}

FName UItemInstanceObject::GetName() const
{
	return item.GetName();
}

FItem UItemInstanceObject::GetItem() const
{
	return FItem(item.GetItem());
}

int32 UItemInstanceObject::GetWear() const
{
	return item.GetWear();
}

void UItemInstanceObject::ApplyWear(int32 amount)
{
	item.ApplyWear(amount);
}

void UItemInstanceObject::Repair()
{
	item.Repair();
}

bool UItemInstanceObject::IsBroken() const
{
	return item.IsBroken();
}
