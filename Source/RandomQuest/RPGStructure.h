// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGLocation.h"

/**
 * 
 */
class RANDOMQUEST_API RPGStructure : public RPGLocation
{
public:
	RPGStructure(const FName& structureName, const FName& structureType, RPGLocation* parentLocation);
	RPGStructure();
	~RPGStructure() override;
};
