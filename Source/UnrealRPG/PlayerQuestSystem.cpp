// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerQuestSystem.h"

UPlayerQuestSystem::UPlayerQuestSystem()
{
}

void UPlayerQuestSystem::InitializeQuestSystem()
{
    //Quest.QuestNPCName = FString{};
    //Quest.QuestDialog = FString{};
    //Quest.MINCount = 0;
    //Quest.MAXCount = 0;
    //Quest.QuestItemName = FString{};
    //Quest.QuestRequireCount = 0;
    //Quest.GainExp = 0;

    //ChangeQuestData.Broadcast();
}

void UPlayerQuestSystem::SetNewQuest(const FQuestData& Data)
{
    Quest = Data;

    ChangeQuestData.Broadcast();
}

void UPlayerQuestSystem::SetUpdateQuest()
{
}

int32 UPlayerQuestSystem::ClearQuest()
{
    //Quest.QuestNPCName = FString{};
    //Quest.QuestDialog = FString{};
    //Quest.MINCount = 0;
    //Quest.MAXCount = 0;
    //Quest.QuestItemName = FString{};
    //Quest.QuestRequireCount = 0;
    //Quest.GainExp = 0;
   
    //보상을 받을 수 있게 처리하고 가지고있는 퀘스트 데이터를 초기화한다
    Quest = FQuestData{};

    ChangeQuestData.Broadcast();
    
    return Quest.GainExp;
}