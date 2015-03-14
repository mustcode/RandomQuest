// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGAttributes;
class RPGInventory;

/**
 * 
 */
class RANDOMQUEST_API RPGMonster
{
public:
	RPGMonster();
	~RPGMonster();

protected:
	RPGAttributes* attributes;
	RPGInventory* inventory;
};
