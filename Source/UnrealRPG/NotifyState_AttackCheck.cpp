// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_AttackCheck.h"
#include "GameFramework/Actor.h"
#include "MonsterCharacterBase.h"
#include "PlayerCharacterBase.h"

UNotifyState_AttackCheck::UNotifyState_AttackCheck()
{
}

void UNotifyState_AttackCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (nullptr != MeshComp && nullptr != MeshComp->GetOwner())
	{
		if (MeshComp->GetOwner()->ActorHasTag(FName(TEXT("Player"))))
		{
			APlayerCharacterBase* MeshOwner = Cast<APlayerCharacterBase>(MeshComp->GetOwner());
			MeshOwner->ChangeCollisionProfile(true);
		}
		else if (MeshComp->GetOwner()->ActorHasTag(FName(TEXT("Monster"))))
		{
			AMonsterCharacterBase* MeshOwner = Cast<AMonsterCharacterBase>(MeshComp->GetOwner());
			MeshOwner->ChangeCollisionProfile(true);
		}
		else
		{
			return;//No Tag is Error
		}
	}
}

void UNotifyState_AttackCheck::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	//auto MeshOwner = MeshComp->GetOwner();

	//FHitResult HitResult;
	//FCollisionQueryParams Params(NAME_None, false, MeshOwner);

	//float AttackRange = 100.f;
	//float AttackRadius = 22.f;

	//FVector OwnerLocation = MeshOwner->GetActorLocation();
	//FVector WeaponLocation = MeshComp->GetSocketLocation(FName(TEXT("weapon")));
	//FVector ForwardVector = MeshOwner->GetActorForwardVector();

	//bool bResult = MeshComp->GetWorld()->SweepSingleByChannel(
	//	OUT HitResult,
	//	WeaponLocation,
	//	WeaponLocation + ForwardVector * AttackRange,
	//	FQuat::Identity,
	//	ECollisionChannel::ECC_Pawn,
	//	FCollisionShape::MakeSphere(AttackRadius),
	//	Params);

	//FVector Vec = ForwardVector * AttackRange;
	//FVector Center = WeaponLocation + Vec * 0.5f;
	//float HalfHeight = AttackRange * 0.5f + AttackRadius;
	//FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	//FColor DrawColor;

	//if (bResult)
	//	DrawColor = FColor::Green;
	//else
	//	DrawColor = FColor::Red;

	//DrawDebugCapsule(MeshComp->GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);

	//if (bResult && HitResult.Actor.IsValid())
	//{
	//	//Owner가 어떤 타입인지에 따라 Stat캐스팅 다르게 할 것
	//	FDamageEvent DamageEvent;
	//
	//	if (0 == MeshOwner->Tags.Num())
	//	{
	//		//Error!
	//		//배치하는 Actor는 무조건 tag를 가질 예정
	//		//에디터에서 발생하는 임시 Actor는 tag가 없으므로(?) 판단하지 말기
	//		UE_LOG(LogTemp, Log, TEXT("No Tag Actor! Error!"));
	//		
	//		return;
	//	}

	//	AController* OwnerController = Cast<APawn>(MeshOwner)->GetController();

	//	if (MeshOwner->ActorHasTag(FName(TEXT("Player"))))
	//	{
	//		if (FName(TEXT("Monster")) == HitResult.Actor->Tags[0])
	//		{
	//			UStatComponent* StatComp = Cast<UStatComponent>(MeshOwner->GetComponentByClass(UStatComponent::StaticClass()));
	//			HitResult.Actor->TakeDamage(StatComp->GetAtk(), DamageEvent, OwnerController, MeshOwner);
	//			UE_LOG(LogTemp, Log, TEXT("HitActor : %s"), *HitResult.Actor->GetName());
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("Player is not attack other actor except [Monster] : %s"), *HitResult.Actor->GetName());
	//		}
	//	}
	//	else if (MeshOwner->ActorHasTag(FName(TEXT("Monster"))))
	//	{
	//		if (FName(TEXT("Player")) == HitResult.Actor->Tags[0])
	//		{
	//			UMonsterStatComponent* StatComp = Cast<UMonsterStatComponent>(MeshOwner->GetComponentByClass(UMonsterStatComponent::StaticClass()));
	//			HitResult.Actor->TakeDamage(StatComp->GetAtk(), DamageEvent, OwnerController, MeshOwner);
	//			UE_LOG(LogTemp, Log, TEXT("HitActor : %s"), *HitResult.Actor->GetName());
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("Monster is not attack other actor except [Player] : %s"), *HitResult.Actor->GetName());
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Error!!!!"));
	//	}
	//}
}

void UNotifyState_AttackCheck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (nullptr != MeshComp && nullptr != MeshComp->GetOwner())
	{
		if (MeshComp->GetOwner()->ActorHasTag(FName(TEXT("Player"))))
		{
			APlayerCharacterBase* MeshOwner = Cast<APlayerCharacterBase>(MeshComp->GetOwner());
			MeshOwner->ChangeCollisionProfile(false);
		}
		else if (MeshComp->GetOwner()->ActorHasTag(FName(TEXT("Monster"))))
		{
			AMonsterCharacterBase* MeshOwner = Cast<AMonsterCharacterBase>(MeshComp->GetOwner());
			MeshOwner->ChangeCollisionProfile(false);
		}
		else
		{
			return;//No Tag is Error
		}
	}
}
