#include "CustomButtonWidget.h"

// Component
#include "Components/Button.h"
#include "Components/SizeBox.h"

void UCustomButtonWidget::Show() {
  Super::Show();

  if (IsValid(m_pButton)) m_pButton->SetVisibility(ESlateVisibility::Visible);
}

void UCustomButtonWidget::Hide() {
  Super::Hide();

  if (IsValid(m_pButton)) m_pButton->SetVisibility(ESlateVisibility::Hidden);
}

void UCustomButtonWidget::NativeConstruct()  {
  Super::NativeConstruct();

  SetSize(m_vSize);
}

void UCustomButtonWidget::SynchronizeProperties() {
  Super::SynchronizeProperties();

  SetSize(m_vSize);
}

void UCustomButtonWidget::SetSize(FVector2D _vNewSize) {
  if (IsValid(m_pSizeBox)) {
    m_pSizeBox->SetWidthOverride(_vNewSize.X);
    m_pSizeBox->SetHeightOverride(_vNewSize.Y);
  }
}