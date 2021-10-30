#include "menu_item.h"

MenuItem::MenuItem(MenuState m_state, std::string m_title) {
  state = m_state;
  this->SetTitle(m_title);
  visible = true;
  previous = NULL;
  next = NULL;
}

std::string MenuItem::GetTitle() {
  return title;
}

void MenuItem::SetTitle(std::string m_title) {
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

MenuState MenuItem::GetState() {
  return state;
}

void MenuItem::AddItemBefore(MenuItem* item) {
  item->SetNext(this);
  item->SetPrevious(this->GetPrevious());
  this->SetPrevious(item);
}

void MenuItem::AddItemAfter(MenuItem* item) {
  item->SetPrevious(this);
  item->SetNext(this->GetNext());
  this->SetNext(item);
}

void MenuItem::AddItemStart(MenuItem* item) {
  if (this->GetPrevious() == NULL) {
    item->SetNext(this);
    this->SetPrevious(item);
  } else {
    this->GetPrevious()->AddItemStart(item);
  }
}

void MenuItem::AddItemEnd(MenuItem* item) {
  if (this->GetNext() == NULL) {
    item->SetPrevious(this);
    this->SetNext(item);
  } else {
    this->GetNext()->AddItemEnd(item);
  }
}
