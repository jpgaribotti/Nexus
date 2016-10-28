#ifndef NEXUS_BUTTON_HPP
#define NEXUS_BUTTON_HPP

#include <memory>
#include <utility>
#include <vector>
#include "Nexus/Nexus.hpp"
#include "Nexus/MixIns/Contains.hpp"
#include "Nexus/MixIns/Draw.hpp"
#include "Nexus/MixIns/GetChildren.hpp"

namespace nx {

template <class LeftClick>
class Button
  : public Nexus<Button<LeftClick>>,
    public mx::ContainsCommon<Button<LeftClick>>,
    public mx::DrawCommon<Button<LeftClick>> {
  friend class Nexus<Button<LeftClick>>;
  friend class mx::ContainsCommon<Button<LeftClick>>;
  friend class mx::DrawCommon<Button<LeftClick>>;

  public:
    Button(LeftClick&& leftClick);

    void AddChild(std::unique_ptr<INexus> child);

  protected:
    enum class Command {
      None,
      LeftRelease
    };
    bool ProcessInputImpl(sf::Event event, const sf::RenderTarget& target);
    void SetOffsetImpl(sf::Vector2f off);
    void SetOriginImpl(sf::Vector2f pos);
    void UpdateImpl();

    std::vector<std::unique_ptr<INexus>> children_;
    LeftClick leftClick_;
    sf::Vector2f origin_;
    sf::Vector2f offset_;
    Command command_;
};

template <class LeftClick>
std::unique_ptr<Button<LeftClick>> MakeButton(LeftClick&& leftClick) {
  return std::make_unique<Button<LeftClick>>(
      std::forward<LeftClick>(leftClick));
}

template <class LeftClick>
Button<LeftClick>::Button(LeftClick&& leftClick)
  : leftClick_(std::forward<LeftClick>(leftClick)), origin_(), offset_(),
    command_() {}

template <class LeftClick>
bool Button<LeftClick>::ProcessInputImpl(
    sf::Event event, const sf::RenderTarget& target) {
  if (event.type == sf::Event::MouseButtonReleased) {
    if (event.mouseButton.button == sf::Mouse::Button::Left) {
      auto posMouse = target.mapPixelToCoords(sf::Vector2i(
          event.mouseButton.x, event.mouseButton.y));
      if (mx::ContainsCommon<Button<LeftClick>>::ContainsImpl(posMouse)) {
        command_ = Command::LeftRelease;
        return true;
      }
    }
  }
  return false;
}

template <class LeftClick>
void Button<LeftClick>::SetOffsetImpl(sf::Vector2f off) {
  offset_ = off;
  auto pos = origin_ + offset_;
  for (const auto& child : children_) {
    child->SetOrigin(pos);
  }
}

template <class LeftClick>
void Button<LeftClick>::SetOriginImpl(sf::Vector2f origin) {
  origin_ = origin;
  auto pos = origin_ + offset_;
  for (const auto& child : children_) {
    child->SetOrigin(pos);
  }
}

template <class LeftClick>
void Button<LeftClick>::UpdateImpl() {
  for (const auto& child : children_) {
    child->Update();
  }
  switch (command_) {
    case Command::None:
      return;
    case Command::LeftRelease:
      leftClick_();
      break;
  }
  command_ = Command::None;
}

template <class LeftClick>
void Button<LeftClick>::AddChild(std::unique_ptr<INexus> child) {
  child->SetOrigin(origin_ + offset_);
  children_.push_back(std::move(child));
}

}

#endif /* NEXUS_BUTTON_HPP */
