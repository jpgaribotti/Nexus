#include "Nexus/Image.hpp"

namespace nx {

template <>
void Image<sf::Text>::SetOffsetImpl(sf::Vector2f off) {
  auto position = drawable_.getPosition() - offset_;
  offset_ = off;
  drawable_.setPosition(
      int(position.x + offset_.x + .5f), int(position.y + offset_.y + .5f));
}

template<>
void Image<sf::Text>::SetOriginImpl(sf::Vector2f pos) {
  drawable_.setPosition(
      int(pos.x + offset_.x + .5f), int(pos.y + offset_.y + .5f));
}

}
