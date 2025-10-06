#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillTree.generated.h"

enum class ENodeState : uint8 {
	Locked	  UMETA(DisplayName = "Locked"),
	Available UMETA(DisplayName = "Available"),
	Unlocked  UMETA(DisplayName = "Unlocked")
};

struct FSkillNode {
#pragma region Constructors
	/**
	 * @brief 
	 * @param InId 
	 * @param InCost 
	 */
	FSkillNode(FName _sId = NAME_None, int32 _iUnlockCost = 0);
#pragma endregion

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
   * @brief Unlocked parent nodes required to unlock this one.
   */
	TArray<TWeakPtr<FSkillNode>> m_lRequiredParents;
#pragma endregion 

#pragma region Relationships
	/**
	 * @brief Children nodes connected to this one.
	 */
	TArray<TWeakPtr<FSkillNode>> m_lChildren;

	/**
	 * @brief Parent node of this one.
	 */
	TWeakPtr<FSkillNode> m_pParent = nullptr;
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

	/**
	 * @brief @TOFILL
	 * @param _iCurrentPoints 
	 * @return 
	 */
	bool CanUnlock(int32 _iCurrentPoints) const;
#pragma endregion
};

// Data
class UDataTable;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeStateChanged, FName);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JPB_PAVJ_UI_API USkillTree : public UActorComponent
{
	GENERATED_BODY()
	
public:
#pragma region Data
	/**
	 * @brief Data Table containing Skill Node data.
	 */
	TObjectPtr<UDataTable> m_pNodeData;

	/**
	 * @brief @TOFILL
	 */
	void BuildFromDataTable();

	/**
	 * @brief @TOFILL
	 * @param _rOutIds 
	 */
	void GetAllNodeIds(TArray<FName>& _rOutNodeIds) const;
#pragma endregion

#pragma region Node
	/**
	 * @brief @TOFILL
	 */
	FOnNodeStateChanged OnNodeChanged;
	
	/**
	 * @brief @TOFILL
	 * @param NodeId 
	 * @param OutCost 
	 * @return 
	 */
	bool TryUnlockNode(const FName& _rNodeId, int32& _rCurrentPoints);

	/**
	 * @brief @TOFILL
	 * @param NodeId 
	 * @return 
	 */
	TSharedPtr<FSkillNode> GetNode(const FName& _rNodeId) const;
#pragma endregion

private:
#pragma region Containers
	/**
	 * @brief @TOFILL
	 */
	TMap<FName, TSharedPtr<FSkillNode>> m_mNodes;
#pragma endregion
};