// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCDialog.h"
//#include "CustomEnum.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UNPCDialog::UNPCDialog()
{
}

void UNPCDialog::CreateNPCDialog(const EPlayerQuestState State, FName NPCName, bool IsSameNPC)
{
    DataInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!IsValid(DataInstance))
    {
        return;
    }

    QuestNPCName = NPCName;

    switch (State)
    {
    case EPlayerQuestState::EMPTY:
    {
        AcceptQuestDialog();
        break;
    }
    case EPlayerQuestState::ACCEPTED:
    {
        CommonDialog();
        break;
    }
    case EPlayerQuestState::COMPLETE:
    {
        //����Ʈ�� �Ϸ��� �������� ��ȭ�� ������ npc�� ����Ʈ�� �� npc�� �ƴ϶�� �Ϲ� Dialog�� �����Ѵ�
        if (IsSameNPC)
        {
            CompleteQuestDialog();
        }
        else
        {
            CommonDialog();
        }
        break;
    }
    default:
    {
        return;
    }
    }

    //return CombineDialogArray;
}

void UNPCDialog::ResetDialogAndQuestData()
{
    CombineDialogArray.Empty();
   
    CombineQuest.QuestNPCName = FString{};
    CombineQuest.QuestDialog = FString{};
    CombineQuest.MINCount = 0;
    CombineQuest.MAXCount = 0;
    CombineQuest.QuestItemName = FString{};
    CombineQuest.QuestRequireCount = 0;
    CombineQuest.GainExp = 0;
}

//����Ʈ ���� �� : CommonStart%d + QuestStartDialog%d + QuestDialog%d + QuestEndDialog%d
void UNPCDialog::AcceptQuestDialog()
{
    //CommonStart%d
    int32 SectionNum = FMath::RandRange(0, 4);
    FString InttoString = FString::FromInt(SectionNum);

    FString DialogName = TEXT("CommonStart");
    DialogName += FString::FromInt(SectionNum);

    FDialogData* DialogData = DataInstance->GetDialogData(FName(DialogName));
    CombineDialogArray.Emplace(DialogData->NPCDialog);

    CombineQuestDialog();
}

//����Ʈ�� ���� ������ �� : CommonStart%d
void UNPCDialog::CommonDialog()
{
    //CommonStart%d
    int32 SectionNum = FMath::RandRange(0, 4);
    FString InttoString = FString::FromInt(SectionNum);

    FString DialogName = TEXT("CommonStart");
    DialogName += FString::FromInt(SectionNum);

    FDialogData* DialogData = DataInstance->GetDialogData(FName(DialogName));
    CombineDialogArray.Emplace(DialogData->NPCDialog);
}

//����Ʈ�� �Ϸ��� �� : QuestFinish%d
void UNPCDialog::CompleteQuestDialog()
{
    int32 SectionNum = FMath::RandRange(0, 4);
    FString InttoString = FString::FromInt(SectionNum);

    FString DialogName = TEXT("QuestFinish");
    DialogName += FString::FromInt(SectionNum);

    FDialogData* DialogData = DataInstance->GetDialogData(FName(DialogName));
    CombineDialogArray.Emplace(DialogData->NPCDialog);
}

void UNPCDialog::CombineQuestDialog()
{
    //QuestStartDialog%d
    int32 SectionNum = FMath::RandRange(0, 1);
    FString InttoString = FString::FromInt(SectionNum);

    FString DialogName = TEXT("QuestStartDialog");
    DialogName += FString::FromInt(SectionNum);

    FQuestData* QuestData = DataInstance->GetQuestData(FName(DialogName));
    if (nullptr != QuestData)
    {
        CombineDialogArray.Emplace(QuestData->QuestDialog);
    }

    //QuestDialog%d
    SectionNum = FMath::RandRange(0, 4);
    InttoString = FString::FromInt(SectionNum);

    DialogName = TEXT("QuestDialog");
    DialogName += FString::FromInt(SectionNum);

    QuestData = DataInstance->GetQuestData(FName(DialogName));
    if (nullptr != QuestData)
    {
        int32 RequiredNum = FMath::RandRange(QuestData->MINCount, QuestData->MAXCount);
        auto test = FString::FromInt(RequiredNum);
        QuestData->QuestDialog.ReplaceInline(TEXT("%d"), *(FString::FromInt(RequiredNum)));
        CombineDialogArray.Emplace(QuestData->QuestDialog);

        //���յ� ����Ʈ ���� �����ϱ�
        CombineQuest.QuestNPCName = QuestNPCName.ToString();
        CombineQuest.QuestDialog = QuestData->QuestDialog;
        CombineQuest.QuestItemName = QuestData->QuestItemName;
        CombineQuest.QuestRequireCount = RequiredNum;
        CombineQuest.GainExp = QuestData->GainExp;
    }

    //FString stringtest = TEXT("item : {0} count : {1}");
    //FString test = FString::Format(*stringtest, { TEXT("tree"), FString::FromInt(1) });
    //UE_LOG(LogTemp, Log, TEXT("test : %s]"), *test);

    //QuestEndDialog%d
    SectionNum = FMath::RandRange(0, 1);
    InttoString = FString::FromInt(SectionNum);

    DialogName = TEXT("QuestEndDialog");
    DialogName += FString::FromInt(SectionNum);

    QuestData = DataInstance->GetQuestData(FName(DialogName));
    if (nullptr != QuestData)
    {
        CombineDialogArray.Emplace(QuestData->QuestDialog);
    }
}