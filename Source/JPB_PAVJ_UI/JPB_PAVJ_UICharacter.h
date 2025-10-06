// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "JPB_PAVJ_UICharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

// Component
class USkillTree;

// Widget
class USkillTreeWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AJPB_PAVJ_UICharacter : public ACharacter {
#pragma region Template Defaults
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Handle Tree Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HandleTreeAction;

public:
	AJPB_PAVJ_UICharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for open/close skill tree */
	void HandleSkillTree(const FInputActionValue& Value);

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion

#pragma region Getters
	/**
	 * @brief @TOFILL
	 * @return 
	 */
	int32 GetCurrentSkillPoints() const;
#pragma endregion

protected:
#pragma region Native Functions
	virtual void BeginPlay() override;
#pragma endregion

#pragma region Widget
	/**
	 * @brief 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JParamade|UI", meta = (DisplayName = "Skill Tree Widget Class"))
	TSubclassOf<USkillTreeWidget> m_pSkillTreeWidgetClass;

	/**
   * @brief @TOFILL
   */
	TObjectPtr<USkillTreeWidget> m_pSkillTreeWidget = nullptr;
#pragma endregion

private:
#pragma region Skill Tree
	/**
	 * @brief @TOFILL
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Skill Tree Component", AllowPrivateAccess = true));
	TObjectPtr<USkillTree> m_pSkillTreeComponent;

	/**
	 * @brief @TOFILL
	 */
	UPROPERTY(EditAnywhere, Category = "Skill Tree", meta = (DisplayName = "Current Skill Points"))
	int32 m_iCurrentSkillPoints = 9;
#pragma endregion
};

