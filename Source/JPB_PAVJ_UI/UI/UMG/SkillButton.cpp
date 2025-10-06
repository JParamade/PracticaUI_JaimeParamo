#include "SkillButton.h"

// Animation
#include "Animation/WidgetAnimation.h"

// Character
#include "JPB_PAVJ_UI/JPB_PAVJ_UICharacter.h"

// Component
#include "Components/Button.h"
#include "Components/SizeBox.h"

// Skill Tree
#include "JPB_PAVJ_UI/UI/SkillTree.h"

void USkillButton::Show() {
  Super::Show();
}

void USkillButton::Hide() {
  Super::Hide();
}

TWeakPtr<FSkillNode> USkillButton::GetBoundNode() const {
  return m_pBoundNode;
}

void USkillButton::InitializeWithNode(TSharedPtr<FSkillNode> _pNode, AJPB_PAVJ_UICharacter* _pOwner) {
  m_pBoundNode = _pNode;
  m_pOwningCharacter = _pOwner;
  UpdateVisualsFromNode();
}

void USkillButton::NativeConstruct() {
  Super::NativeConstruct();

  if (IsValid(m_pButton)) {
    if (!m_pButton->OnPressed.IsAlreadyBound(this, &USkillButton::OnButtonPressed)) {
      m_pButton->OnPressed.AddDynamic(this, &USkillButton::OnButtonPressed);
    }
    if (!m_pButton->OnReleased.IsAlreadyBound(this, &USkillButton::OnButtonReleased)) {
      m_pButton->OnReleased.AddDynamic(this, &USkillButton::OnButtonReleased);
    }
  }
}

void USkillButton::SynchronizeProperties() {
  Super::SynchronizeProperties();

  SetupDynamicMaterial();
}

void USkillButton::NativeTick(const FGeometry& _rMyGeometry, float _fInDeltaTime) {
  Super::NativeTick(_rMyGeometry, _fInDeltaTime);

  if (TSharedPtr<FSkillNode> pNode = m_pBoundNode.Pin()) {
    if (!pNode->IsUnlocked()) {
      if (m_bIsPressed) {
        m_fVibrationElapsedTime += _fInDeltaTime * m_fVibrationSpeed;
        m_vVibrationOffset = {
          FMath::Sin(m_fVibrationElapsedTime) * m_fVibrationAmplitude,
          FMath::Cos(m_fVibrationElapsedTime) * m_fVibrationAmplitude
        };

        if (IsValid(m_pSizeBox)) m_pSizeBox->SetRenderTranslation(m_vVibrationOffset);

        m_fFillAmount = FMath::Clamp(m_fFillAmount + _fInDeltaTime * m_fFillSpeed, .0f, 1.f);

        if (m_fFillAmount >= 1.f) {
          OnUnlockRequested.Broadcast(pNode->m_sId);
          if (IsValid(m_pUnlockedAnimation)) PlayAnimation(m_pUnlockedAnimation, .0f, 1, EUMGSequencePlayMode::Forward);
        }
      }
      else m_fFillAmount = FMath::Clamp(m_fFillAmount - _fInDeltaTime * m_fFillSpeed, .0f, 1.f);
    }

    if (IsValid(m_pFillDynamicMaterial)) m_pFillDynamicMaterial->SetScalarParameterValue("FillAmount", m_fFillAmount);
  }
}

void USkillButton::OnButtonPressed() {
  if (TSharedPtr<FSkillNode> pNode = m_pBoundNode.Pin()) {
    if (!pNode->CanUnlock(m_pOwningCharacter->GetCurrentSkillPoints())) {
      if (IsValid(m_pOwningCharacter) && IsValid(m_pUnavailableAnimation)) {
        PlayAnimation(m_pUnavailableAnimation, .0f, 1, EUMGSequencePlayMode::Forward);
        return;
      }
    }
  }

  m_bIsPressed = true;
  m_fVibrationElapsedTime = 0.f;

  if (IsValid(m_pSizeBox)) m_pSizeBox->SetRenderScale({ m_fPressedScale, m_fPressedScale });
}

void USkillButton::OnButtonReleased() {
  if (TSharedPtr<FSkillNode> pNode = m_pBoundNode.Pin()) if (pNode->IsLocked()) return;

  m_bIsPressed = false;

  if (IsValid(m_pSizeBox)) {
    m_pSizeBox->SetRenderTranslation(FVector2D::ZeroVector);
    m_pSizeBox->SetRenderScale(FVector2D::UnitVector);
  }
}

void USkillButton::UpdateVisualsFromNode() {
  if (TSharedPtr<FSkillNode> pNode = m_pBoundNode.Pin()) {
    if (IsValid(m_pButton) && IsValid(m_pLockedTexture) && IsValid(m_pFillDynamicMaterial)) {
      FButtonStyle oNewStyle = m_pButton->GetStyle();

      if (pNode->IsLocked()) {
        oNewStyle.Normal.SetResourceObject(m_pLockedTexture);
        oNewStyle.Hovered.SetResourceObject(m_pLockedTexture);
        oNewStyle.Pressed.SetResourceObject(m_pLockedTexture);
        oNewStyle.Disabled.SetResourceObject(m_pLockedTexture);
      }
      else {
        oNewStyle.Normal.SetResourceObject(m_pFillDynamicMaterial);
        oNewStyle.Hovered.SetResourceObject(m_pFillDynamicMaterial);
        oNewStyle.Pressed.SetResourceObject(m_pFillDynamicMaterial);
        oNewStyle.Disabled.SetResourceObject(m_pFillDynamicMaterial);

        m_pFillDynamicMaterial->SetScalarParameterValue("FillAmount", pNode->IsUnlocked() ? 1.f : .0f);
      }
    }
  }
}

void USkillButton::SetupDynamicMaterial() {
  if (!IsValid(m_pBaseMaterial)) m_pBaseMaterial = GetClass()->GetDefaultObject<USkillButton>()->m_pBaseMaterial;
  if (!IsValid(m_pLockedTexture)) m_pLockedTexture = GetClass()->GetDefaultObject<USkillButton>()->m_pLockedTexture;

  if (IsValid(m_pBaseMaterial)) {
    m_pFillDynamicMaterial = UMaterialInstanceDynamic::Create(m_pBaseMaterial, this);

    FButtonStyle oNewStyle = m_pButton->GetStyle();

    oNewStyle.Normal.SetResourceObject(m_pFillDynamicMaterial);
    oNewStyle.Hovered.SetResourceObject(m_pFillDynamicMaterial);
    oNewStyle.Pressed.SetResourceObject(m_pFillDynamicMaterial);
    oNewStyle.Disabled.SetResourceObject(m_pFillDynamicMaterial);

    m_pButton->SetStyle(oNewStyle);
  }

  if (IsValid(m_pFillDynamicMaterial) && IsValid(m_pBaseTexture)) {
    m_pFillDynamicMaterial->SetTextureParameterValue("BaseTexture", m_pBaseTexture);
  }
}