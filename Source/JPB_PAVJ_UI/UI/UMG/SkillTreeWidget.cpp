#include "SkillTreeWidget.h"

// Component
#include "Components/Image.h"
#include "Components/TextBlock.h"

// Widget
#include "JPB_PAVJ_UI/UI/UMG/SkillButton.h"

void USkillTreeWidget::Show() {
  Super::Show();

  if (IsValid(m_pBackground)) m_pBackground->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pTitle)) m_pTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pPoints)) m_pPoints->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USkillTreeWidget::Hide() {
  Super::Hide();

  if (IsValid(m_pBackground)) m_pBackground->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pTitle)) m_pTitle->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pPoints)) m_pPoints->SetVisibility(ESlateVisibility::Hidden);
}

void USkillTreeWidget::NativeConstruct() {
  Super::NativeConstruct();

  if (IsValid(m_pSkillButton1)) m_lWidgets.Add(m_pSkillButton1);
  if (IsValid(m_pSkillButton2)) m_lWidgets.Add(m_pSkillButton2);
  if (IsValid(m_pSkillButton3)) m_lWidgets.Add(m_pSkillButton3);
  if (IsValid(m_pSkillButton4)) m_lWidgets.Add(m_pSkillButton4);
  if (IsValid(m_pSkillButton5)) m_lWidgets.Add(m_pSkillButton5);
  if (IsValid(m_pSkillButton6)) m_lWidgets.Add(m_pSkillButton6);
}