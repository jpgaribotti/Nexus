#ifndef NEXUS_IMAGE_HPP
#define NEXUS_IMAGE_HPP

#include "Nexus/Nexus.hpp"
#include "Nexus/MixIns/ProcessInput.hpp"
#include "Nexus/MixIns/Update.hpp"
#include "SFML/Graphics/Text.hpp"

namespace nx {

template <class Drawable>
class Image
  : public Nexus<Image<Drawable>>,
    public mx::ProcessInputNull<Image<Drawable>>,
    public mx::UpdateNull<Image<Drawable>> {
  friend class Nexus<Image<Drawable>>;
  public:
    Image(Drawable drawable) :
        drawable_(std::move(drawable)), offset_(drawable_.getPosition()) {}

    bool ContainsImpl(sf::Vector2f pos) const;
    void DrawImpl(sf::RenderTarget& target) const;
    void SetOffsetImpl(sf::Vector2f off);
    void SetOriginImpl(sf::Vector2f pos);

    Drawable& GetDrawable();
    const Drawable& GetDrawable() const;

  private:
    Drawable drawable_;
    sf::Vector2f offset_;
};

template <class Drawable>
Drawable& Image<Drawable>::GetDrawable() {
  return drawable_;
}

template <class Drawable>
const Drawable& Image<Drawable>::GetDrawable() const {
  return drawable_;
}

template <class Drawable>
bool Image<Drawable>::ContainsImpl(sf::Vector2f point) const {
  return drawable_.getGlobalBounds().contains(point);
}

template <class Drawable>
void Image<Drawable>::DrawImpl(sf::RenderTarget& target) const {
  target.draw(drawable_);
}

template <class Drawable>
void Image<Drawable>::SetOffsetImpl(sf::Vector2f off) {
  auto position = drawable_.getPosition() - offset_;
  offset_ = off;
  drawable_.setPosition(position + offset_);
}

template <class Drawable>
void Image<Drawable>::SetOriginImpl(sf::Vector2f pos) {
  drawable_.setPosition(pos + offset_);
}

template <>
void Image<sf::Text>::SetOffsetImpl(sf::Vector2f off);

template<>
void Image<sf::Text>::SetOriginImpl(sf::Vector2f pos);

}

#endif /* NEXUS_IMAGE_HPP */
