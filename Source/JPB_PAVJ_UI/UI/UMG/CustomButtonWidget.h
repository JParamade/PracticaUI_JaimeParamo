#pragma once

#include "CoreMinimal.h"
#include "JPB_PAVJ_UI/UI/UMG/CustomUserWidget.h"
#include "CustomButtonWidget.generated.h"

// Component
class UButton;

UCLASS()
class JPB_PAVJ_UI_API UCustomButtonWidget : public UCustomUserWidget {
  GENERATED_BODY()

  /**
   * @brief Displays the UMG elements of this Widget on screen.
   */
  virtual void Show() override;
  /**
   * @brief Hides the UMG elements of this Widget.
   */
  virtual void Hide() override;

protected:
  /**
   * @brief Called when the widget is constructed.
   */
  virtual void NativeConstruct() override;

  /**
   * @brief @TOFILL
   */
  TObjectPtr<UButton> m_pButton;
};