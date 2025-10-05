#include "CustomUserWidget.h"

void UCustomUserWidget::Show() {
  m_bWidgetVisible = true;

  for (TObjectPtr<UCustomUserWidget> pCustomUserWidget : m_lWidgets) {
    if (IsValid(pCustomUserWidget)) pCustomUserWidget->Show();
  }
}

void UCustomUserWidget::Hide() {
  m_bWidgetVisible = false;

  for (TObjectPtr<UCustomUserWidget> pCustomUserWidget : m_lWidgets) {
    if (IsValid(pCustomUserWidget)) pCustomUserWidget->Hide();
  }
}

bool UCustomUserWidget::IsWidgetVisible() const {
  return m_bWidgetVisible;
}

void UCustomUserWidget::NativeConstruct() {
  Super::NativeConstruct();
}