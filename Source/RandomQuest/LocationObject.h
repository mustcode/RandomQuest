// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "LocationObject.generated.h"

class RPGLocation;

/**
 * 
 */
UCLASS(BlueprintType)
class RANDOMQUEST_API ULocationObject : public UObject
{
	GENERATED_BODY()
public:
	ULocationObject();
	~ULocationObject() override;

	template <typename T>
	FORCEINLINE void Init(FName locationName, FName locationType, ULocationObject* parentLocation)
	{
		location = new T(locationName, locationType, (parentLocation) ? parentLocation->location : nullptr);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	FName GetName() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	FName GetType() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetChildrenCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	FName GetChildName(int32 index) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool HasChild(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddGate(FName name);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool HasGate(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddConnection(FName gateName, ULocationObject* connectTo, FName entrance);

	RPGLocation* location;
};
