// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGItem;

/**
 * 
 */
class RANDOMQUEST_API RPGInventory
{
public:
	RPGInventory();
	~RPGInventory();

	void AddItem(RPGItem* item);
	void RemoveItem(RPGItem* item);
	int ItemsCount() const;
	RPGItem* GetItem(int index) const;
	RPGItem* FindItem(FName name) const;
	const TArray<RPGItem*>& GetItems() const;

private:
	TArray<RPGItem*> items;
	float weightLimit;
	float spaceLimit;
};
