#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUserWidget.generated.h"

UCLASS()
class JPB_PAVJ_UI_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region Visibility
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

	/**
	 * @brief @TOFILL
	 * @return
	 */
	UFUNCTION(BlueprintCallable, Category = "Custom User Widget", meta = (DisplayName = "Is Visible"))
	virtual bool IsWidgetVisible() const;
#pragma endregion

protected:
#pragma region Native Functions
	/**
	 * @brief Called when the widget is constructed.
	 */
	virtual void NativeConstruct() override;
#pragma endregion

#pragma region Containers
	/**
	 * @brief List of non focusable UI elements contained in the widget.
	 */
	UPROPERTY()
	TArray<TObjectPtr<UCustomUserWidget>> m_lWidgets;
#pragma endregion

#pragma region Flags
	/**
	 * @brief @TOFILL
	 */
	bool m_bWidgetVisible = false;
#pragma endregion
};