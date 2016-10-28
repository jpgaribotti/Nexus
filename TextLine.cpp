#include "Nexus/TextLine.hpp"

namespace nx {

float TextLine::GetPositionNext() const {
  if (children_.empty()) {
    return position_.x;
  }
  auto bounds = children_.back().getGlobalBounds();
  return bounds.left + bounds.width;
}

float TextLine::GetNextLineHeight() const {
  return spacing_ + position_.y;
}

void TextLine::AddText(sf::Text text) {
  const auto& font = *text.getFont();
  const auto size = int(text.getCharacterSize());
  const auto spacing = font.getLineSpacing(size);
  if (size_ < size) size_ = size;
  if (spacing_ < spacing) spacing_ = spacing;
  text.setPosition(GetPositionNext(), position_.y + size_ - size);
  children_.push_back(std::move(text));
}

void TextLine::SetLineSpacing(int spacing) {
  spacing_ = spacing;
}

bool TextLine::ContainsImpl(sf::Vector2f point) const {
  for (const auto& child : children_) {
    if (child.getGlobalBounds().contains(point)) {
      return true;
    }
  }
  return false;
}

void TextLine::DrawImpl(sf::RenderTarget& target) const {
  for (const auto& child : children_) {
    target.draw(child);
  }
}

void TextLine::SetOffsetImpl(sf::Vector2f) {

}

void TextLine::SetOriginImpl(sf::Vector2f pos) {
  for (auto& child : children_) {
    auto offset = child.getPosition() - position_;
    child.setPosition(pos + offset);
  }
  position_ = pos;
}

}
