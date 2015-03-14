// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "StructureActor.h"
#include "LocationObject.h"

void AStructureActor::Init(ULocationObject* location)
{
	structure = location;
}
