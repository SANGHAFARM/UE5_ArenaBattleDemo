// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

// 델리게이트 선언
// 체력 값이 0이 되었을 때 발행할 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);

// 체력 변경이 발생했을 때 발행할 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLEDEMO_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Getter
	FORCEINLINE float GetMaxHP() { return MaxHp; }
	FORCEINLINE float GetCurrentHP() { return CurrentHp; }

	// 대미지 전달 함수
	float ApplyDamage(float InDamage);

protected:
	// HP가 변경되었을 때 실행할 함수
	void SetHp(float NewHp);

public:
	// 체력 값이 0이 되었을 때 발행되는 델리게이트
	FOnHpZeroDelegate OnHpZero;
	// 체력 변경이 발생했을 때 발행할 델리게이트
	FOnHpChangedDelegate OnHpChanged;
	
	// 스탯
protected:
	// 최대 체력 값
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MaxHp;

	// 현재 체력 값
	// Transient : 현재 체력 값은 게임을 진행할 때마다 바뀌는 값이므로
	// 디스크에 명시적으로 저장이 필요하지 않을 수 있음 (공간 절약 가능)
	// 따라서 Transient로 지정가능
	UPROPERTY(Transient, VisibleAnywhere, Category = Stat)
	float CurrentHp;
};