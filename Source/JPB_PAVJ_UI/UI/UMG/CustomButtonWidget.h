#pragma once

#include "CoreMinimal.h"
#include "JPB_PAVJ_UI/UI/UMG/CustomUserWidget.h"
#include "CustomButtonWidget.generated.h"

// Component
class UButton;
class USizeBox;

UCLASS()
class JPB_PAVJ_UI_API UCustomButtonWidget : public UCustomUserWidget {
  GENERATED_BODY()

public:
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
  virtual void SynchronizeProperties() override;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UButton> m_pButton;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USizeBox> m_pSizeBox;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Layout", meta = (DisplayName = "Size", ClampMin = "0.0"))
  FVector2D m_vSize = FVector2D(100.f, 100.f);

private:
  void SetSize(FVector2D _vNewSize);
};