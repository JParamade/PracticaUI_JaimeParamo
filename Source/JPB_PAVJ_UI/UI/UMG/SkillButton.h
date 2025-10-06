#pragma once

#include "CoreMinimal.h"
#include "CustomButtonWidget.h"
#include "SkillButton.generated.h"

// Animation
class UWidgetAnimation;

// Component
class UImage;
class UTextBlock;

// Character
class AJPB_PAVJ_UICharacter;

// Skill Tree
struct FSkillNode;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnlockRequested, FName);

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

#pragma region Getters
  /**
   * @brief @TOFILL
   * @return 
   */
  TWeakPtr<FSkillNode> GetBoundNode() const;
#pragma endregion

#pragma region Skill Tree
  /**
   * @brief @TOFILL
   * @param _pNode 
   */
  void InitializeWithNode(TSharedPtr<FSkillNode> _pNode, AJPB_PAVJ_UICharacter* _pOwner);

  /**
   * @brief @TOFILL
   */
  UFUNCTION()
  void UpdateVisualsFromNode();

  /**
   * @brief @TOFILL
   */
  FOnUnlockRequested OnUnlockRequested;
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

#pragma region Animations
  /**
   * @brief 
   */
  UPROPERTY(meta = (BindWidgetAnim), Transient)
  TObjectPtr<UWidgetAnimation> m_pUnavailableAnimation;
  /**
   * @brief
   */
  UPROPERTY(meta = (BindWidgetAnim), Transient)
  TObjectPtr<UWidgetAnimation> m_pUnlockedAnimation;
#pragma endregion

#pragma region Components
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UImage> m_pForeground;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UImage> m_pLock;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UTextBlock> m_pCost;
#pragma endregion

#pragma region Node
  /**
   * @brief @TOFILL
   */
  TWeakPtr<FSkillNode> m_pBoundNode;
#pragma endregion

#pragma region Player
  /**
   * @brief
   */
  AJPB_PAVJ_UICharacter* m_pOwningCharacter = nullptr;
#pragma endregion

#pragma region Style
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JParamade|UI|Style", meta = (DisplayName = "Base Material"))
  TObjectPtr<UMaterialInterface> m_pBaseMaterial = nullptr;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI|Style", meta = (DisplayName = "Base Texture"))
  TObjectPtr<UTexture2D> m_pBaseTexture = nullptr;

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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Vibration Speed"))
  float m_fVibrationSpeed = 80.f;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Vibration Amplitude"))
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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Pressed Scale"))
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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JParamade|UI|Feedback", meta = (DisplayName = "Fill Speed"))
  float m_fFillSpeed = 1.f;

  /**
   * @brief @TOFILL
   */
  TObjectPtr<UMaterialInstanceDynamic> m_pFillDynamicMaterial = nullptr;
#pragma endregion
};