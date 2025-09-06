#include "SkillTree.h"

bool FSkillNode::IsLocked() const { return m_eState == ENodeState::Locked; }

bool FSkillNode::IsAvailable() const { return m_eState == ENodeState::Available; }

bool FSkillNode::IsUnlocked() const { return m_eState == ENodeState::Unlocked; }