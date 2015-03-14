// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGItem
{
public:
	RPGItem();
	virtual ~RPGItem();

protected:
	FName name;
	FName type;
	bool isEquipable;
	bool isEquipped;
};
