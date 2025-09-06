#include "CustomUserWidget.h"

void UCustomUserWidget::Show() {
  // @TOCOMMENT
  for (TObjectPtr<UCustomUserWidget> pCustomUserWidget : m_lWidgets) {
    if (IsValid(pCustomUserWidget)) pCustomUserWidget->Show();
  }
}

void UCustomUserWidget::Hide() {
  // @TOCOMMENT
  for (TObjectPtr<UCustomUserWidget> pCustomUserWidget : m_lWidgets) {
    if (IsValid(pCustomUserWidget)) pCustomUserWidget->Hide();
  }
}

void UCustomUserWidget::NativeConstruct() {
  Super::NativeConstruct();

}