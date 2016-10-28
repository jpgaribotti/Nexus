#ifndef NEXUS_MIXINS_SETOFFSET_HPP
#define NEXUS_MIXINS_SETOFFSET_HPP

namespace nx {
namespace mx {

template <class Container>
void SetOffsetImplShared(const Container& children, sf::Vector2f pos) {
  for (const auto& child : children) {
    child->SetOrigin(pos);
  }
}

template <class Derived>
struct SetOffsetBase {
  void SetOffsetImpl(sf::Vector2f off) {
    auto& derived = *static_cast<Derived*>(this);
    derived.GetOffset() = off;
    auto pos = derived.GetOrigin() + derived.GetOffset();
    SetOffsetImplShared(derived.GetChildren(), pos);
  }
};

template <class Derived>
struct SetOffsetCommon {
  void SetOffsetImpl(sf::Vector2f off) {
    auto& derived = *static_cast<Derived*>(this);
    derived.offset_ = off;
    auto pos = derived.origin_ + derived.offset_;
    SetOffsetImplShared(derived.children_, pos);
  }
};

template <class Derived>
struct SetOffsetNull {
  void SetOffsetImpl(sf::Vector2f) {}
};

}
}

#endif /* NEXUS_MIXINS_SETOFFSET_HPP */
