// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentPage/FastMenuComboBoxKey.h"


UFastMenuComboBoxKey::UFastMenuComboBoxKey()
{
	OnGenerateContentWidget.BindUFunction(this, "OnGenerateContentWidgetCallback");
	OnGenerateItemWidget.BindUFunction(this, "OnGenerateItemWidgetCallback");
}

