#ifndef NEXUS_FOCUSABLE_HPP
#define NEXUS_FOCUSABLE_HPP

#include "Nexus/Nexus.hpp"

namespace nx {

template <class Base>
class Focusable {
  protected:
    enum class Focus {
      NoChange,
      Gained,
      Lost
    };
  public:
    Focus CheckFocusEvent(
        sf::Event event, const sf::RenderTarget& target) const;
};

template <class Base>
typename Focusable<Base>::Focus Focusable<Base>::CheckFocusEvent(
    sf::Event event, const sf::RenderTarget& target) const {
  if (event.type == sf::Event::MouseMoved) {
    const auto& base = static_cast<const Base&>(*this);
    auto mousePos = target.mapPixelToCoords(sf::Vector2i(
        event.mouseMove.x, event.mouseMove.y));
    auto contained = std::find_if(
        base.children_.begin(), base.children_.end(),
        [mousePos](const auto& child) {
          return child->Contains(mousePos);
        }) != base.children_.end();
    if (!base.focused_ && contained) {
      return Focus::Gained;
    }
    if (base.focused_ && !contained) {
      return Focus::Lost;
    }
  }
  return Focus::NoChange;
}

}

#endif /* NEXUS_FOCUSABLE_HPP */
