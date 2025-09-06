#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillTree.generated.h"

enum class ENodeState : uint8 {
	Locked	  UMETA(DisplayName = "Locked"),
	Available UMETA(DisplayName = "Available"),
	Unlocked  UMETA(DisplayName = "Unlocked")
};

struct FSkillNode {
#pragma region Identification
	/**
	 * @brief Unique ID for this node.
	 */
	FName m_sId;
#pragma endregion

#pragma region State
	/**
	 * @brief Whether this node has been unlocked.
	 */
	ENodeState m_eState = ENodeState::Locked;
#pragma endregion

#pragma region Unlock Requirements
	/**
	 * @brief Skill points required to unlock this node.
	 */
	int32 m_iUnlockCost;

	/**
   * @brief Children nodes connected to this one.
   */
	TArray<TObjectPtr<FSkillNode>> m_lRequiredParents;
#pragma endregion 

#pragma region Relationships
	/**
	 * @brief Children nodes connected to this one.
	 */
	TArray<TObjectPtr<FSkillNode>> m_lChildren;

	/**
	 * @brief Parent node of this one.
	 */
	TObjectPtr<FSkillNode> m_pParent = nullptr;
#pragma endregion

#pragma region Helper Functions
	/**
   * @brief Checks if this node is currently locked.
   * @return True if the node status is Locked.
   */
	bool IsLocked() const;
	
	/**
   * @brief Checks if this node is available to be unlocked by the player.
   * @return True if the node status is Available.
   */
	bool IsAvailable() const;
	
	/**
	 * @brief Checks if this node has already been unlocked.
	 * @return True if the node status is Unlocked.
	 */
	bool IsUnlocked() const; 
#pragma endregion
};

UCLASS()
class JPB_PAVJ_UI_API USkillTree : public UObject
{
	GENERATED_BODY()
	
public:

};