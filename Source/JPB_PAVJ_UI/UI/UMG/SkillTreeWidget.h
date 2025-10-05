#pragma once

#include "CoreMinimal.h"
#include "CustomUserWidget.h"
#include "SkillTreeWidget.generated.h"

// Component
class UImage;
class UTextBlock;

// Widget
class USkillButton;

UCLASS()
class JPB_PAVJ_UI_API USkillTreeWidget : public UCustomUserWidget
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
#pragma endregion

#pragma region Components
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UImage> m_pBackground;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UTextBlock> m_pTitle;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UTextBlock> m_pPoints;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton1;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton2;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton3;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton4;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton5;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton6;
#pragma endregion
};
