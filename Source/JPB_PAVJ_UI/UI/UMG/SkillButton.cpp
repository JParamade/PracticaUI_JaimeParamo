#include "SkillButton.h"

// Component
#include "Components/Button.h"
#include "Components/SizeBox.h"

void USkillButton::Show() {
  Super::Show();
}

void USkillButton::Hide() {
  Super::Hide();
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

  SetupDynamicMaterial();
}

void USkillButton::SynchronizeProperties() {
  Super::SynchronizeProperties();

  SetupDynamicMaterial();
}

void USkillButton::NativeTick(const FGeometry& _rMyGeometry, float _fInDeltaTime) {
  Super::NativeTick(_rMyGeometry, _fInDeltaTime);

  if (m_bIsPressed) {
    m_fVibrationElapsedTime += _fInDeltaTime * m_fVibrationSpeed;
    m_vVibrationOffset = {
      FMath::Sin(m_fVibrationElapsedTime) * m_fVibrationAmplitude,
      FMath::Cos(m_fVibrationElapsedTime) * m_fVibrationAmplitude
    };

    if (IsValid(m_pSizeBox)) m_pSizeBox->SetRenderTranslation(m_vVibrationOffset);

    m_fFillAmount = FMath::Clamp(m_fFillAmount + _fInDeltaTime * m_fFillSpeed, .0f, 1.f);
  }
  else m_fFillAmount = FMath::Clamp(m_fFillAmount - _fInDeltaTime * m_fFillSpeed, .0f, 1.f);

  if (IsValid(m_pFillDynamicMaterial)) m_pFillDynamicMaterial->SetScalarParameterValue("FillAmount", m_fFillAmount);
}

void USkillButton::OnButtonPressed() {
  m_bIsPressed = true;
  m_fVibrationElapsedTime = 0.f;

  if (IsValid(m_pSizeBox)) m_pSizeBox->SetRenderScale({ m_fPressedScale, m_fPressedScale });
}

void USkillButton::OnButtonReleased() {
  m_bIsPressed = false;

  if (IsValid(m_pSizeBox)) {
    m_pSizeBox->SetRenderTranslation(FVector2D::ZeroVector);
    m_pSizeBox->SetRenderScale(FVector2D::UnitVector);
  }
}

void USkillButton::SetupDynamicMaterial() {
  if (IsValid(m_pMaterialBase)) {
    UMaterialInstanceDynamic* pDynamicMaterial = UMaterialInstanceDynamic::Create(m_pMaterialBase, this);

    FButtonStyle oNewStyle = m_pButton->GetStyle();

    oNewStyle.Normal.SetResourceObject(pDynamicMaterial);
    oNewStyle.Hovered.SetResourceObject(pDynamicMaterial);
    oNewStyle.Pressed.SetResourceObject(pDynamicMaterial);
    oNewStyle.Disabled.SetResourceObject(pDynamicMaterial);
    m_pButton->SetStyle(oNewStyle);

    m_pFillDynamicMaterial = pDynamicMaterial;
  }

  if (IsValid(m_pFillDynamicMaterial) && IsValid(m_pTexture)) {
    m_pFillDynamicMaterial->SetTextureParameterValue("BaseTexture", m_pTexture);
  }
}