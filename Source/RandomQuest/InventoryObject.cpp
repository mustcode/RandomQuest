// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "InventoryObject.h"
#include "RPGInventory.h"

UInventoryObject::UInventoryObject()
	: inventory(nullptr)
	, gold(0)
	, silver(0)
	, copper(0)
{
}

UInventoryObject::~UInventoryObject()
{
	if (inventory)
		delete inventory;
}

void UInventoryObject::Init()
{
	inventory = new RPGInventory;
}
