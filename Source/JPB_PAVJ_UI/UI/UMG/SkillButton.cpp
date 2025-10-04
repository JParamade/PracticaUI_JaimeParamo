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
    m_pButton->OnPressed.AddDynamic(this, &USkillButton::OnButtonPressed);
    m_pButton->OnReleased.AddDynamic(this, &USkillButton::OnButtonReleased);
  }
}

void USkillButton::NativeTick(const FGeometry& _rMyGeometry, float _fInDeltaTime) {
  Super::NativeTick(_rMyGeometry, _fInDeltaTime);

  if (m_bIsVibrating && IsValid(m_pSizeBox)) {
    m_fVibrationElapsedTime += _fInDeltaTime * m_fVibrationSpeed;
    m_vVibrationOffset = {
      FMath::Sin(m_fVibrationElapsedTime) * m_fVibrationAmplitude,
      FMath::Cos(m_fVibrationElapsedTime) * m_fVibrationAmplitude
    };

    m_pSizeBox->SetRenderTranslation(m_vVibrationOffset);
  }
}

void USkillButton::OnButtonPressed() {
  m_bIsVibrating = true;
  m_fVibrationElapsedTime = 0.f;

  if (IsValid(m_pSizeBox)) m_pSizeBox->SetRenderScale({ m_fPressedScale, m_fPressedScale });
}

void USkillButton::OnButtonReleased() {
  m_bIsVibrating = false;

  if (IsValid(m_pSizeBox)) {
    m_pSizeBox->SetRenderTranslation(FVector2D::ZeroVector);
    m_pSizeBox->SetRenderScale(FVector2D::UnitVector);
  }
}