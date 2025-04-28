// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"

#include "GameData/ABGameSingleton.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	//MaxHp = 200.0f;
	//CurrentHp = MaxHp;
	CurrentLevel = 1.0f;
	AttackRadius = 50.0f;
}

// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// 레벨 스탯 데이터 설정
	SetLevelStat(static_cast<int32>(CurrentLevel));
	
	// 게임이 시작되면 최대 체력인 상태로 설정
	SetHp(BaseStat.MaxHp);
}

void UABCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	// 유효한 레벨 범위로 고정
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UABGameSingleton::Get().CharacterMaxLevel);

	// 게임 싱글톤으로부터 레벨 데이터 가져오기
	BaseStat = UABGameSingleton::Get().GetCharacterStat(CurrentLevel);
	
	// 설정한 값에 문제 없는지 확인
	check(BaseStat.MaxHp > 0.0f);
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
	//CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	// 체력 변경 이벤트 발행
	OnHpChanged.Broadcast(CurrentHp);
}