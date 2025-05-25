// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ItemObject.h"

void USS_ItemObject::RotateImage()
{
	ItemInfo.bIsRotated = !ItemInfo.bIsRotated;

	ItemInfo.IconSize = FIntPoint(ItemInfo.IconSize.Y, ItemInfo.IconSize.X);
}
