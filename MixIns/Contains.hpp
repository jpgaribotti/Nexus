#ifndef NEXUS_MIXINS_CONTAINSCOMMON_HPP
#define NEXUS_MIXINS_CONTAINSCOMMON_HPP

namespace nx {
namespace mx {

template <class Container>
bool ContainsImplShared(const Container& children, sf::Vector2f point) {
  for (const auto& child : children) {
    if (child->Contains(point)) {
      return true;
    }
  }
  return false;
}

template <class Derived>
struct ContainsBase {
  bool ContainsImpl(sf::Vector2f point) const {
    return ContainsImplShared(
        static_cast<const Derived*>(this)->GetChildren(), point);
  }
};

template <class Derived>
struct ContainsCommon {
  bool ContainsImpl(sf::Vector2f point) const {
    return ContainsImplShared(
        static_cast<const Derived*>(this)->children_, point);
  }
};

template <class Derived>
struct ContainsNull {
  bool ContainsImpl(sf::Vector2f) const {
    return false;
  }
};

}
}

#endif /* NEXUS_MIXINS_CONTAINSCOMMON_HPP */
