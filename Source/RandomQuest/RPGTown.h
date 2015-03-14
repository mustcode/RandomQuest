// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGLocation.h"

/**
 * 
 */
class RANDOMQUEST_API RPGTown : public RPGLocation
{
public:
	RPGTown(const FName& locationName, const FName& locationType, RPGLocation* parentLocation);
	RPGTown();
	~RPGTown() override;
};
