#pragma once

#include "CoreMinimal.h"
#include "CustomUserWidget.h"
#include "SkillTreeWidget.generated.h"

// Animation
class UWidgetAnimation;

// Character
class AJPB_PAVJ_UICharacter;

// Component
class UImage;
class UTextBlock;

// Skill Tree
class USkillTree;

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

#pragma region Skill Tree
  /**
   * @brief @TOFILL
   * @param SkillTree 
   * @param NodeIds 
   */
  void InitializeFromSkillTree(USkillTree* _pSkillTree, const TArray<FName>& _rNodeIds, AJPB_PAVJ_UICharacter* _pOwner);

  /**
   * @brief 
   * @param _sNodeId 
   */
  void HandleRequestUnlockNode(FName _sNodeId);
#pragma endregion

protected:
#pragma region Native Functions
	/**
	 * @brief Called when the widget is constructed.
	 */
	virtual void NativeConstruct() override;
#pragma endregion

#pragma region Binding Functions
  /**
   * @brief @TOFILL
   * @param _sNodeId 
   */
  UFUNCTION()
  void OnNodeUpdated(FName _sNodeId);

  /**
   * @brief @TOFILL
   * @param _iNewPoints 
   */
  UFUNCTION()
  void UpdatePointsText(int32 _iNewPoints);
#pragma endregion

#pragma region Containers
  UPROPERTY()
  TArray<TObjectPtr<USkillButton>> m_lNodeWidgets;
#pragma endregion

#pragma region Animations
  /**
   * @brief
   */
  UPROPERTY(meta = (BindWidgetAnim), Transient)
  TObjectPtr<UWidgetAnimation> m_pPointsAnimation;
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
  TObjectPtr<UTextBlock> m_pHealthText;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton1;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UImage> m_pConnector1;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton2;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UTextBlock> m_pStaminaText;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton3;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UImage> m_pConnector2;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton4;

  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UTextBlock> m_pMovementText;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton5;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<UImage> m_pConnector3;
  /**
   * @brief @TOFILL
   */
  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  TObjectPtr<USkillButton> m_pSkillButton6;
#pragma endregion

#pragma region Skill Tree
  TObjectPtr<USkillTree> m_pSkillTree = nullptr;
#pragma endregion 
};
