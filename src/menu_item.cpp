#include "menu_item.h"

MenuItem::MenuItem(MenuState m_state, char* m_title) {
  state = m_state;
  this->SetTitle(m_title);
  visible = true;
  previous = NULL;
  next = NULL;
}

char* MenuItem::GetTitle() {
  return title;
}

void MenuItem::SetTitle(char* m_title) {
  title = m_title;
}

MenuItem* MenuItem::GetPrevious() {
  return previous;
}

void MenuItem::SetPrevious(MenuItem* item) {
  previous = item;
}

MenuItem* MenuItem::GetNext() {
  return next;
}

void MenuItem::SetNext(MenuItem* item) {
  next = item;
}

MenuItem* MenuItem::GetPreviousVisible() {
  if (this->GetPrevious() == NULL ||
      this->GetPrevious()->IsVisible()) {
    return this->GetPrevious();
  } else {
    return this->GetPrevious()->GetPreviousVisible();
  }
}

MenuItem* MenuItem::GetNextVisible() {
  if (this->GetNext() == NULL ||
      this->GetNext()->IsVisible()) {
    return this->GetNext();
  } else {
    return this->GetNext()->GetNextVisible();
  }
}

bool MenuItem::IsVisible() {
  return visible;
}

void MenuItem::SetVisibility(bool m_visible) {
  visible = m_visible;
}

void MenuItem::ToggleVisibility() {
  visible = !visible;
}
