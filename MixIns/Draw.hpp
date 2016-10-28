#ifndef NEXUS_MIXINS_DRAWCOMMON_HPP
#define NEXUS_MIXINS_DRAWCOMMON_HPP

namespace nx {
namespace mx {

template <class Container>
void DrawImplShared(const Container& children, sf::RenderTarget& target) {
  for (const auto& child : children) {
    child->Draw(target);
  }
}

template <class Derived>
struct DrawBase {
  void DrawImpl(sf::RenderTarget& target) const {
    DrawImplShared(static_cast<const Derived*>(this)->GetChildren(), target);
  }
};

template <class Derived>
struct DrawCommon {
  void DrawImpl(sf::RenderTarget& target) const {
    DrawImplShared(static_cast<const Derived*>(this)->children_, target);
  }
};

}
}

#endif /* NEXUS_MIXINS_DRAWCOMMON_HPP */
