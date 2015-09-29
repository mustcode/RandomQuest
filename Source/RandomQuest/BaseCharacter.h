// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameDataComponent.h"
#include "BaseCharacter.generated.h"

class UCharacterObject;
class UWorldDataInstance;

UCLASS(ClassGroup = RPG)
class RANDOMQUEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init(UCharacterObject* characterObject);

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool TryUseSkill(FName name);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<FSkill> GetSkills() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetAttributeValue(FName attribute) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetMaxAttributeValue(FName attribute) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetMinAttributeValue(FName attribute) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void ApplyHealing(ABaseCharacter* healer, int32 amount, FName healingType);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void ApplyDamage(ABaseCharacter* originator, int32 amount, FName damageType);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnHealed(ABaseCharacter* healer, int32 amount, bool isCritical, FName healingType);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnDamaged(ABaseCharacter* originator, int32 amount, bool isCritical, FName damageType);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnExecuteSkillCommand(const TArray<FSkillCommand>& commands);

	UPROPERTY(BlueprintReadOnly, Category = RPG)
	UCharacterObject* character;

protected:
	virtual void OnHealed_Implementation(ABaseCharacter* healer, int32 amount, bool isCritical, FName healingType);
	virtual void OnDamaged_Implementation(ABaseCharacter* originator, int32 amount, bool isCritical, FName damageType);
	virtual void OnExecuteSkillCommand_Implementation(const TArray<FSkillCommand>& commands);
	UWorldDataInstance* GetWorldData() const;

	float activeSkillTime;
	int32 activeCommandIndex;
};
