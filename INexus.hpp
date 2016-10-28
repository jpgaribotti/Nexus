#ifndef NEXUS_INEXUS_HPP
#define NEXUS_INEXUS_HPP

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "RuntimeArray.hpp"

namespace nx {

class INexus
{
  public:
    virtual ~INexus() {};

    virtual bool Contains(sf::Vector2f point) const = 0;
    virtual void Draw(sf::RenderTarget& target) const = 0;
    virtual bool ProcessInput(
        sf::Event event, const sf::RenderTarget& target) = 0;
    virtual void SetOffset(sf::Vector2f pos) = 0;
    virtual void SetOrigin(sf::Vector2f pos) = 0;
    virtual void Update() = 0;
};

}

#endif /* NEXUS_INEXUS_HPP */
