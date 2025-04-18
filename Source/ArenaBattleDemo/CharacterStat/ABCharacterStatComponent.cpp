// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}

// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// 게임이 시작되면 최대 체력인 상태로 설정
	SetHp(MaxHp);
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	// 대미지 처리
	const float PrevHp = CurrentHp;

	// 대미지 보정 값
	// 오류로 인해 전달된 대미지가 음수일 수 있기 때문에 음수인 경우는 0으로 설정
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	// 대미지 계산
	SetHp(PrevHp - ActualDamage);

	// 죽었는지 (체력이 모두 소진되었는지) 확인
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)
{
	// 현재 체력 업데이트
	CurrentHp = FMath::Clamp<float>(NewHp, 0, MaxHp);

	// 체력 변경 이벤트 발행
	OnHpChanged.Broadcast(CurrentHp);
}
