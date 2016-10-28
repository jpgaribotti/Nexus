#ifndef NEXUS_MIXINS_SETORIGIN_HPP
#define NEXUS_MIXINS_SETORIGIN_HPP

namespace nx {
namespace mx {

template <class Container>
void SetOriginImplShared(const Container& children, sf::Vector2f pos) {
  for (const auto& child : children) {
    child->SetOrigin(pos);
  }
}

template <class Derived>
struct SetOriginBase {
  void SetOriginImpl(sf::Vector2f origin) {
    auto& derived = *static_cast<Derived*>(this);
    derived.GetOrigin() = origin;
    auto pos = derived.GetOrigin() + derived.GetOffset();
    SetOriginImplShared(derived.GetChildren(), pos);
  }
};

template <class Derived>
struct SetOriginCommon {
  void SetOriginImpl(sf::Vector2f origin) {
    auto& derived = *static_cast<Derived*>(this);
    derived.origin_ = origin;
    auto pos = derived.origin_ + derived.offset_;
    SetOriginImplShared(derived.children_, pos);
  }
};

template <class Derived>
struct SetOriginNull {
  void SetOriginImpl(sf::Vector2f) {}
};

}
}

#endif /* NEXUS_MIXINS_SETORIGIN_HPP */
