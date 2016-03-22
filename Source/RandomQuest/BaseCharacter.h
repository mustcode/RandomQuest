// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameDataComponent.h"
#include "RPGEquipSlot.h"
#include "RPGDamageInfo.h"
#include "RPGHealInfo.h"
#include "BaseCharacter.generated.h"

class UCharacterObject;
class UItemInstanceObject;
class UWorldDataInstance;

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 attack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 defense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isCritical;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isFumbled;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName damageType;

	FDamageInfo() {}
	FDamageInfo(const RPGDamageInfo& damageInfo);
};

USTRUCT(BlueprintType)
struct FHealInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 healAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isCritical;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isFumbled;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName healingType;

	FHealInfo() {}
	FHealInfo(const RPGHealInfo& healInfo);
};

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
	bool TryUseSkill(FName name, AActor* target);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<FSkill> GetSkills() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<FTrait> GetTraits() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetAttributeValue(FName attribute) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetMaxAttributeValue(FName attribute) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetMinAttributeValue(FName attribute) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	float GetAttributeValueAsPecent(FName attribute) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool IsUsingSkill() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void HoldSkillTime();

	UFUNCTION(BlueprintCallable, Category = RPG)
	void ResumeSkillTime();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool IsHoldingSkillTime() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void ApplyHealing(ABaseCharacter* healer, int32 amount, FName healingType);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void ApplyDamage(ABaseCharacter* originator, int32 amount, FName damageType);

	UFUNCTION(BlueprintCallable, Category = RPG)
	FDamageInfo NormalAttack(ABaseCharacter* defender);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnHealed(ABaseCharacter* healer, const FHealInfo& healInfo);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnDamaged(ABaseCharacter* originator, const FDamageInfo& damageInfo);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnSkillActivated(FName name, AActor* target);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnExecuteSkillCommand(const TArray<FSkillCommand>& commands);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnItemEquipped(UItemInstanceObject* item);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnItemRemoved(UItemInstanceObject* item);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void EquipItem(UItemInstanceObject* item);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void RemoveItem(UItemInstanceObject* item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool CanEquip(const UItemInstanceObject* item) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool IsEquipped(const UItemInstanceObject* item) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<UItemInstanceObject*>& GetEquipments() const;

	UPROPERTY(BlueprintReadOnly, Category = RPG)
	UCharacterObject* character;

protected:
	virtual void OnHealed_Implementation(ABaseCharacter* healer, const FHealInfo& healInfo);
	virtual void OnDamaged_Implementation(ABaseCharacter* originator, const FDamageInfo& damageInfo);
	virtual void OnSkillActivated_Implementation(FName name, AActor* target);
	virtual void OnExecuteSkillCommand_Implementation(const TArray<FSkillCommand>& commands);
	virtual void OnItemEquipped_Implementation(UItemInstanceObject* item);
	virtual void OnItemRemoved_Implementation(UItemInstanceObject* item);
	UWorldDataInstance* GetWorldData() const;
	RPGEquipSlot* GetEquipSlot(const UItemInstanceObject* item) const;
	void PostDamagedLogic(UWorldDataInstance* world);

	float activeSkillTime;
	int32 activeCommandIndex;
	bool holdSkillTime;
};
