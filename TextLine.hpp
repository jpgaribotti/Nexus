#ifndef NEXUS_TEXTLINE_HPP
#define NEXUS_TEXTLINE_HPP

#include <vector>
#include "SFML/Graphics/Text.hpp"
#include "Nexus/Nexus.hpp"
#include "Nexus/MixIns/Contains.hpp"
#include "Nexus/MixIns/GetChildren.hpp"
#include "Nexus/MixIns/ProcessInput.hpp"
#include "Nexus/MixIns/Update.hpp"

namespace nx {

class TextLine
  : public Nexus<TextLine>,
    public mx::GetChildrenNull<TextLine>,
    public mx::ProcessInputNull<TextLine>,
    public mx::UpdateNull<TextLine> {
  friend class Nexus;
  public:
    float GetPositionNext() const;
    float GetNextLineHeight() const;
    void AddText(sf::Text text);
    void SetLineSpacing(int spacing);

  protected:
    bool ContainsImpl(sf::Vector2f point) const;
    void DrawImpl(sf::RenderTarget& target) const;
    void SetOffsetImpl(sf::Vector2f off);
    void SetOriginImpl(sf::Vector2f pos);

    std::vector<sf::Text> children_;
    sf::Vector2f position_;
    int size_;
    int spacing_;
};

}

#endif /* NEXUS_TEXTLINE_HPP */
