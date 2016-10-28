#include "Nexus/TextBox.hpp"

#include "BbCodeParser.hpp"
#include "FontStyles.hpp"
#include "ResourceCache.hpp"

namespace nx {

TextBox::TextBox(
    sf::FloatRect bounds, TextFormat format, ResourceCache& cache)
  : cache_(cache), background_(sf::Vector2f(bounds.width, bounds.height)),
    format_(format), left_(), right_(), top_(), bottom_(),
    command_(), firstLine_() {
  background_.setPosition(sf::Vector2f(bounds.left, bounds.top));
  children_.push_back({});
  children_.back().SetOrigin(sf::Vector2f(bounds.left, bounds.top));
}

void TextBox::AppendString(string_view string) {
  AppendString(ToU32String(string));
}

void TextBox::AppendString(u32string_view string) {
  auto bounds = background_.getGlobalBounds();
  bounds.left += left_;
  bounds.width -= (left_ + right_);
  bounds.top += top_;
  bounds.height -= (top_ + bottom_);
  const auto parsed = ParseBbCode(string, format_);
  auto linePos = children_.back().GetPositionNext();
  for (const auto& styled : parsed.text) {
    const auto& font = cache_.GetResource(GetFontStyleKey(
        styled.style.fontKey, styled.style.style));
    auto text = sf::Text("", font, styled.style.size);
    text.setFillColor(styled.style.fillColor);
    text.setStyle(styled.style.style & sf::Text::Underlined);
    if (styled.string.empty()) {
      const auto posY = children_.back().GetNextLineHeight();
      children_.push_back({});
      children_.back().SetOrigin(sf::Vector2f(bounds.left, posY));
      children_.back().SetLineSpacing(font.getLineSpacing(styled.style.size));
      linePos = children_.back().GetPositionNext();
      continue;
    }
    auto codePos = 0;
    auto startPos = 0;
    auto breakPos = 0;
    auto code = 0;
    for (const int end = styled.string.size(); codePos != end; ++codePos) {
      code = styled.string[codePos];
      if (code == ' ') breakPos = codePos;
      linePos += font.getGlyph(code, styled.style.size, false).advance;
      if (linePos > (bounds.width + bounds.left)) {
        auto substr = std::u32string(
            styled.string.data()+startPos, breakPos-startPos);
        text.setString(reinterpret_cast<const sf::Uint32*>(substr.data()));
        children_.back().AddText(text);
        const auto posY = children_.back().GetNextLineHeight();
        children_.push_back({});
        children_.back().SetOrigin(sf::Vector2f(bounds.left, posY));
        linePos = children_.back().GetPositionNext();
        codePos = breakPos;
        startPos = breakPos+1;
      }
    }
    breakPos = styled.string.size();
    auto substr = std::u32string(
        styled.string.data()+startPos, breakPos-startPos);
    text.setString(reinterpret_cast<const sf::Uint32*>(substr.data()));
    children_.back().AddText(text);
  }
  const auto bottomLimit = bounds.top + bounds.height;
  while ((children_.end()-1)->GetNextLineHeight() > bottomLimit) {
    ScrollText(-1);
  }
}

void TextBox::Clear() {
  auto pos = background_.getPosition();
  pos.x += left_; pos.y += top_;
  children_.clear();
  children_.push_back({});
  children_.back().SetOrigin(pos);
}

void TextBox::SetBackgroundFillColor(sf::Color color) {
  background_.setFillColor(color);
}

void TextBox::SetBorders(int left, int right, int top, int bottom) {
  left_ = left; right_ = right; top_ = top; bottom_ = bottom;
  auto pos = background_.getPosition();
  pos.x += left; pos.y += top;
  children_.clear();
  children_.push_back({});
  children_.back().SetOrigin(pos);
}

bool TextBox::ContainsImpl(sf::Vector2f point) const {
  return background_.getGlobalBounds().contains(point);
}

void TextBox::DrawImpl(sf::RenderTarget& target) const {
  target.draw(background_);
  const int end = children_.size();
  const auto bounds = background_.getGlobalBounds();
  const float bottomLimit = bounds.top + bounds.height - bottom_;
  for (auto index = firstLine_; index < end; ++index) {
    const auto& child = children_[index];
    if (!(child.GetNextLineHeight() < bottomLimit)) {
      break;
    }
    child.Draw(target);
  }
}

bool TextBox::ProcessInputImpl(
    sf::Event event, const sf::RenderTarget& target) {
  for (auto childIt = children_.rbegin(), end = children_.rend();
      childIt != end; ++childIt) {
    if (childIt->ProcessInput(event, target))
      return true;
  }
  if (event.type == sf::Event::MouseWheelScrolled) {
    auto posMouse = target.mapPixelToCoords(sf::Vector2i(
        event.mouseWheelScroll.x, event.mouseWheelScroll.y));
    if (ContainsImpl(posMouse)) {
      command_.type = Command::Type::Scroll;
      command_.delta = event.mouseWheelScroll.delta;
      return true;
    }
  }
  return false;
}

void TextBox::SetOffsetImpl(sf::Vector2f) {

}

void TextBox::SetOriginImpl(sf::Vector2f pos) {
  background_.setPosition(pos);
  for (auto& child : children_) {
    child.SetOrigin(pos);
  }
}

void TextBox::UpdateImpl() {
  switch (command_.type) {
    case Command::Type::None:
      return;
    case Command::Type::Scroll:
      ScrollText(command_.delta);
  }
  command_.type = Command::Type::None;
}

void TextBox::ScrollText(int delta) {
  firstLine_ -= delta;
  const int end = children_.size();
  if (firstLine_ < 0) firstLine_ = 0;
  else if (firstLine_ > end-1) firstLine_ = end-1;

  const auto bounds = background_.getGlobalBounds();
  const float topLimit = bounds.top + top_;
  const float bottomLimit = bounds.top + bounds.height - bottom_;
  const float posX = bounds.left + left_;
  auto posY = topLimit;
  for (auto index = firstLine_; index < end; ++index) {
    auto& child = children_[index];
    child.SetOrigin(sf::Vector2f(posX, posY));
    posY = child.GetNextLineHeight();
    if (posY > bottomLimit) break;
  }
}

}
