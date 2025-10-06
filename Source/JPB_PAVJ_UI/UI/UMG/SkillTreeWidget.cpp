#include "SkillTreeWidget.h"

// Character
#include "JPB_PAVJ_UI/JPB_PAVJ_UICharacter.h"

// Component
#include "Components/Image.h"
#include "Components/TextBlock.h"

// Skill Tree
#include "JPB_PAVJ_UI/UI/SkillTree.h"

// Widget
#include "JPB_PAVJ_UI/UI/UMG/SkillButton.h"

void USkillTreeWidget::Show() {
  Super::Show();

  if (IsValid(m_pBackground)) m_pBackground->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pTitle)) m_pTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pPoints)) m_pPoints->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pConnector1)) m_pConnector1->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pConnector2)) m_pConnector2->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pConnector3)) m_pConnector3->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pHealthText)) m_pHealthText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pStaminaText)) m_pStaminaText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  if (IsValid(m_pMovementText)) m_pMovementText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  if (IsValid(m_pSkillTree)) m_pSkillTree->OnNodeChanged.AddUObject(this, &USkillTreeWidget::OnNodeUpdated);
  for (USkillButton* pSkillButton : m_lNodeWidgets) {
    if (!pSkillButton) continue;
    pSkillButton->OnUnlockRequested.AddUObject(this, &USkillTreeWidget::HandleRequestUnlockNode);
  }
}

void USkillTreeWidget::Hide() {
  Super::Hide();

  if (IsValid(m_pBackground)) m_pBackground->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pTitle)) m_pTitle->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pPoints)) m_pPoints->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pConnector1)) m_pConnector1->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pConnector2)) m_pConnector2->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pConnector3)) m_pConnector3->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pHealthText)) m_pHealthText->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pStaminaText)) m_pStaminaText->SetVisibility(ESlateVisibility::Hidden);
  if (IsValid(m_pMovementText)) m_pMovementText->SetVisibility(ESlateVisibility::Hidden);

  if (IsValid(m_pSkillTree)) m_pSkillTree->OnNodeChanged.RemoveAll(this);
  for (USkillButton* pSkillButton : m_lNodeWidgets) {
    if (!pSkillButton) continue;
    pSkillButton->OnUnlockRequested.RemoveAll(this);
  }
}

void USkillTreeWidget::InitializeFromSkillTree(USkillTree* _pSkillTree, const TArray<FName>& _rNodeIds, AJPB_PAVJ_UICharacter* _pOwner) {
  if (!_pSkillTree) return;
  m_pSkillTree = _pSkillTree;

  int32 iCount = FMath::Min(m_lNodeWidgets.Num(), _rNodeIds.Num());
  for (int32 iIndex = 0; iIndex < iCount; ++iIndex) {
    USkillButton* pSkillButton = m_lNodeWidgets[iIndex];
    if (!pSkillButton) continue;

    TSharedPtr<FSkillNode> pNode = _pSkillTree->GetNode(_rNodeIds[iIndex]);
    if (pNode.IsValid()) pSkillButton->InitializeWithNode(pNode, _pOwner);
  }
}

void USkillTreeWidget::HandleRequestUnlockNode(FName _sNodeId) {
  if (!IsValid(m_pSkillTree)) return;

  if (AJPB_PAVJ_UICharacter* pCharacter = Cast<AJPB_PAVJ_UICharacter>(GetOwningPlayerPawn())) {
    int32 iCurrentPoints = pCharacter->GetCurrentSkillPoints();
    m_pSkillTree->TryUnlockNode(_sNodeId, iCurrentPoints);
  }
}

void USkillTreeWidget::NativeConstruct() {
  Super::NativeConstruct();

  if (IsValid(m_pSkillButton1)) {
    m_lWidgets.Add(m_pSkillButton1);
    m_lNodeWidgets.Add(m_pSkillButton1);
  }
  if (IsValid(m_pSkillButton2)) {
    m_lWidgets.Add(m_pSkillButton2);
    m_lNodeWidgets.Add(m_pSkillButton2);
  }
  if (IsValid(m_pSkillButton3)) {
    m_lWidgets.Add(m_pSkillButton3);
    m_lNodeWidgets.Add(m_pSkillButton3);
  }
  if (IsValid(m_pSkillButton4)) {
    m_lWidgets.Add(m_pSkillButton4);
    m_lNodeWidgets.Add(m_pSkillButton4);
  }
  if (IsValid(m_pSkillButton5)) {
    m_lWidgets.Add(m_pSkillButton5);
    m_lNodeWidgets.Add(m_pSkillButton5);
  }
  if (IsValid(m_pSkillButton6)) {
    m_lWidgets.Add(m_pSkillButton6);
    m_lNodeWidgets.Add(m_pSkillButton6);
  }
}

void USkillTreeWidget::OnNodeUpdated(FName _sNodeId) {
  for (USkillButton* pButton : m_lNodeWidgets) {
    if (TSharedPtr<FSkillNode> pNode = pButton->GetBoundNode().Pin()) {
      if (pNode->m_sId == _sNodeId) pButton->UpdateVisualsFromNode();
    }
  }
}