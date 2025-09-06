#include "CustomButtonWidget.h"

// Component
#include "Components/Button.h"

void UCustomButtonWidget::Show() {
  Super::Show();

  m_pButton->SetVisibility(ESlateVisibility::Visible);
}

void UCustomButtonWidget::Hide() {
  Super::Hide();

  m_pButton->SetVisibility(ESlateVisibility::Hidden);
}

void UCustomButtonWidget::NativeConstruct()  {
  Super::NativeConstruct();
}