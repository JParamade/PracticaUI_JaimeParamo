#pragma once

#include "CoreMinimal.h"
#include "CustomButtonWidget.h"
#include "SkillButton.generated.h"

UCLASS()
class JPB_PAVJ_UI_API USkillButton : public UCustomButtonWidget
{
  GENERATED_BODY()

public:
#pragma region Visibility
  /**
   * @brief Displays the UMG elements of this Widget on screen.
   */
  virtual void Show() override;
  /**
   * @brief Hides the UMG elements of this Widget.
   */
  virtual void Hide() override;
#pragma endregion

protected:
#pragma region Native Functions
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
   * @param MyGeometry
   * @param InDeltaTime
   */
  virtual void NativeTick(const FGeometry& _rMyGeometry, float _fInDeltaTime) override;
#pragma endregion

#pragma region Binding Functions
  /**
   * @brief @TOFILL
   */
  UFUNCTION()
  void OnButtonPressed();

  /**
   * @brief @TOFILL
   */
  UFUNCTION()
  void OnButtonReleased();
#pragma endregion

#pragma region Style
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Style", meta = (DisplayName = "Material Base"))
  UMaterialInterface* m_pMaterialBase;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Style", meta = (DisplayName = "Texture"))
  TObjectPtr<UTexture2D> m_pTexture;

  /**
   * @brief 
   */
  void SetupDynamicMaterial();
#pragma endregion

#pragma region State
  /**
   * @brief @TOFILL
   */
  bool m_bIsPressed = false;
#pragma endregion

#pragma region Vibration
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Vibration Speed"))
  float m_fVibrationSpeed = 80.f;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Vibration Amplitude"))
  float m_fVibrationAmplitude = 1.f;
  /**
   * @brief @TOFILL
   */
  FVector2D m_vVibrationOffset = { .0f, .0f };
  /**
   * @brief @TOFILL
   */
  float m_fVibrationElapsedTime = .0f;
#pragma endregion

#pragma region Scale
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Pressed Scale"))
  float m_fPressedScale = 1.05f;
#pragma endregion

#pragma region Fill Color
  /**
   * @brief @TOFILL
   */
  float m_fFillAmount = .0f;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Fill Speed"))
  float m_fFillSpeed = 1.f;

  /**
   * @brief @TOFILL
   */
  TObjectPtr<UMaterialInstanceDynamic> m_pFillDynamicMaterial;
#pragma endregion
};