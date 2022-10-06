// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MonsterBTInterface.h"
#include "BTService_SearchTarget.generated.h"

DECLARE_MULTICAST_DELEGATE(FMonsterChangeState);

/**
 * 
 */
UCLASS()
class UNREALRPG_API UBTService_SearchTarget : public UBTService, public IMonsterBTInterface
{
	GENERATED_BODY()
	
public:
	UBTService_SearchTarget();
		
	//�� �����Ӹ��� ���� ������ �ֱ������� Tick�� ȣ���� ��
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	FMonsterChangeState OnMonsterChangeState;
};