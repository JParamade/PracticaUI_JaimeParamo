#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillNodeData.generated.h"

USTRUCT(BlueprintType)
struct FSkillNodeData {
  GENERATED_BODY()

  /**
   * @brief Unique ID for this node.
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ID"))
  FName m_sId;

  /**
   * @brief Skill points required to unlock this node.
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Unlock Cost"))
  int32 m_iUnlockCost;

  /**
   * @brief Unlocked parent nodes required to unlock this one.
   */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Required Parents"))
  TArray<FName> m_lRequiredParents;
};