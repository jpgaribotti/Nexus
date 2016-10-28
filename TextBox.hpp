#ifndef NEXUS_TEXTBOX_HPP
#define NEXUS_TEXTBOX_HPP

#include "Nexus/Nexus.hpp"

#include <memory>
#include <vector>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Nexus/TextLine.hpp"
#include "ResourceCache.hpp"
#include "StringUtils.hpp"
#include "TextFormat.hpp"
#include "MixIns/GetChildren.hpp"
#include "MixIns/Update.hpp"

namespace nx {

class TextBox
  : public Nexus<TextBox> {
  friend class Nexus;
  public:
    TextBox(
        sf::FloatRect bounds, TextFormat format, ResourceCache& cache);

    void AppendString(string_view string);
    void AppendString(u32string_view string);
    void Clear();
    void SetBackgroundFillColor(sf::Color color);
    void SetBorders(int left, int right, int top, int bottom);

  protected:
    struct Command {
      enum class Type {
        None,
        Scroll
      } type;
      int delta;
    };
    bool ContainsImpl(sf::Vector2f point) const;
    void DrawImpl(sf::RenderTarget& target) const;
    bool ProcessInputImpl(sf::Event event, const sf::RenderTarget& target);
    void SetOffsetImpl(sf::Vector2f off);
    void SetOriginImpl(sf::Vector2f pos);
    void UpdateImpl();

    void ScrollText(int delta);

    ResourceCache& cache_;
    std::vector<TextLine> children_;
    sf::RectangleShape background_;
    TextFormat format_;
    int left_, right_, top_, bottom_;
    Command command_;
    int firstLine_;
};

}

#endif /* NEXUS_TEXTBOX_HPP */
