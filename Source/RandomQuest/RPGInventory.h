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

private:
	TArray<RPGItem*> items;
};
