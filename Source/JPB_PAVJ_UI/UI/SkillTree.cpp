#include "SkillTree.h"

// Data
#include "JPB_PAVJ_UI/Data/SkillNodeData.h"

FSkillNode::FSkillNode(FName _sId, int32 _iUnlockCost) 
  : m_sId(_sId)
  , m_iUnlockCost(_iUnlockCost)
{}

bool FSkillNode::IsLocked() const { return m_eState == ENodeState::Locked; }

bool FSkillNode::IsAvailable() const { return m_eState == ENodeState::Available; }

bool FSkillNode::IsUnlocked() const { return m_eState == ENodeState::Unlocked; }

bool FSkillNode::CanUnlock(int32 _iCurrentPoints) const {
  return IsAvailable() && _iCurrentPoints >= m_iUnlockCost;
}

void USkillTree::BuildFromDataTable() {
  m_mNodes.Reset();

  if (!IsValid(m_pNodeData)) return;

  const FString sContext = TEXT("SkillTreeBuild");
  TArray<FName> lRowNames = m_pNodeData->GetRowNames();

  // Create Nodes.
  for (const FName& rRowName : lRowNames) {
    const FSkillNodeData* pRow = m_pNodeData->FindRow<FSkillNodeData>(rRowName, sContext);
    if (!pRow) continue;

    TSharedPtr<FSkillNode> pNewNode = MakeShared<FSkillNode>(pRow->m_sId, pRow->m_iUnlockCost);
    m_mNodes.Add(pRow->m_sId, pNewNode);
  }

  // Create Relationships.
  for (const FName& rRowName : lRowNames) {
    const FSkillNodeData* pRow = m_pNodeData->FindRow<FSkillNodeData>(rRowName, sContext);
    if (!pRow) continue;

    TSharedPtr<FSkillNode> pThisNode = m_mNodes.FindRef(pRow->m_sId);
    if (!pThisNode.IsValid()) continue;

    for (const FName& rParentId : pRow->m_lRequiredParents) {
      TSharedPtr<FSkillNode> pParentNode = m_mNodes.FindRef(rParentId);
      if (pParentNode.IsValid()) {
        pThisNode->m_lRequiredParents.Add(pParentNode);
        pParentNode->m_lChildren.Add(pThisNode);
      }
    }
  }

  // Set Initial Availability.
  for (TPair<FName, TSharedPtr<FSkillNode>>& rPair : m_mNodes) {
    TSharedPtr<FSkillNode> pNode = rPair.Value;
    if (pNode.IsValid()) {
      if (pNode->m_lRequiredParents.Num() == 0) pNode->m_eState = ENodeState::Available;
      else pNode->m_eState = ENodeState::Locked;
    }
  }
}

void USkillTree::GetAllNodeIds(TArray<FName>& _rOutNodeIds) const {
  _rOutNodeIds.Reset();

  for (const TPair<FName, TSharedPtr<FSkillNode>>& rPair : m_mNodes) _rOutNodeIds.Add(rPair.Key);
}

bool USkillTree::TryUnlockNode(const FName& _rNodeId, int32& _rCurrentPoints) {
  TSharedPtr<FSkillNode> pNode = GetNode(_rNodeId);
  
  // @TOFILL
  if (!pNode.IsValid()) return false;
  if (!pNode->IsAvailable()) return false;
  if (_rCurrentPoints < pNode->m_iUnlockCost) return false;

  _rCurrentPoints -= pNode->m_iUnlockCost;
  pNode->m_eState = ENodeState::Unlocked;
  OnNodeChanged.Broadcast(pNode->m_sId);

  for (TWeakPtr<FSkillNode> pChildWeak : pNode->m_lChildren) {
    if (TSharedPtr<FSkillNode> pChild = pChildWeak.Pin()) {
      bool bAllParentsUnlocked = true;

      for (TWeakPtr<FSkillNode> pRequiredWeak : pChild->m_lRequiredParents) {
        if (TSharedPtr<FSkillNode> pRequired = pRequiredWeak.Pin()) {
          if (!pRequired->IsUnlocked()) {
            bAllParentsUnlocked = false;
            break;
          }
        }
      }

      if (bAllParentsUnlocked && pChild->IsLocked()) pChild->m_eState = ENodeState::Available;
    }
  }

  return true;
}

TSharedPtr<FSkillNode> USkillTree::GetNode(const FName& _rNodeId) const {
  const TSharedPtr<FSkillNode>* pFound = m_mNodes.Find(_rNodeId);
  return pFound ? *pFound : nullptr;
}