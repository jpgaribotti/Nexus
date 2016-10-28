#ifndef NEXUS_NEXUS_HPP
#define NEXUS_NEXUS_HPP

#include "Nexus/INexus.hpp"

namespace nx {

template <class Derived>
class Nexus : public INexus
{
  public:
    bool Contains(sf::Vector2f point) const override;
    void Draw(sf::RenderTarget& target) const override;
    bool ProcessInput(sf::Event event, const sf::RenderTarget& target) override;
    void SetOffset(sf::Vector2f pos) override;
    void SetOrigin(sf::Vector2f pos) override;
    void Update() override;
};

template <class Derived>
bool Nexus<Derived>::Contains(sf::Vector2f point) const {
  return static_cast<const Derived*>(this)->ContainsImpl(point);
}

template <class Derived>
void Nexus<Derived>::Draw(sf::RenderTarget& target) const {
  static_cast<const Derived*>(this)->DrawImpl(target);
}

template <class Derived>
bool Nexus<Derived>::ProcessInput(sf::Event event, const sf::RenderTarget& target) {
  return static_cast<Derived*>(this)->ProcessInputImpl(event, target);
}

template <class Derived>
void Nexus<Derived>::SetOffset(sf::Vector2f pos) {
  static_cast<Derived*>(this)->SetOffsetImpl(pos);
}

template <class Derived>
void Nexus<Derived>::SetOrigin(sf::Vector2f pos) {
  static_cast<Derived*>(this)->SetOriginImpl(pos);
}

template <class Derived>
void Nexus<Derived>::Update() {
  static_cast<Derived*>(this)->UpdateImpl();
}

}

#endif /* NEXUS_NEXUS_HPP */
