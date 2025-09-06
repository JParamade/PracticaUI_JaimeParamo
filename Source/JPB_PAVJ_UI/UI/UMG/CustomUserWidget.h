#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUserWidget.generated.h"

UCLASS()
class JPB_PAVJ_UI_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief Displays the UMG elements of this Widget on screen.
	 */
	UFUNCTION(BlueprintCallable, Category = "Custom User Widget", meta = (DisplayName = "Show"))
	virtual void Show();
	/**
	 * @brief Hides the UMG elements of this Widget.
	 */
	UFUNCTION(BlueprintCallable, Category = "Custom User Widget", meta = (DisplayName = "Hide"))
	virtual void Hide();

protected:
	/**
	 * @brief Called when the widget is constructed.
	 */
	virtual void NativeConstruct() override;

	/**
	 * @brief List of non focusable UI elements contained in the widget.
	 */
	TArray<UCustomUserWidget> m_lWidgets;
};