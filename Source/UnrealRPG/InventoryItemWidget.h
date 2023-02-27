// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UInventoryItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UInventoryItemWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	void UpdateItemImage(class UInventoryItem* ListItemObject);
	void UpdateItemCount(class UInventoryItem* ListItemObject);

private:
	TWeakObjectPtr<class UInventoryItem> PlayerInventoryItem;

	UPROPERTY(Meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount;

};
