#ifndef NEXUS_MIXINS_PROCESSINPUTCOMMON_HPP
#define NEXUS_MIXINS_PROCESSINPUTCOMMON_HPP

namespace nx {
namespace mx {

template <class Container>
bool ProcessInputImplShared(
    const Container& children, sf::Event event,
    const sf::RenderTarget& target) {
  for (auto childIt = children.rbegin(), end = children.rend();
      childIt != end; ++childIt) {
    if ((*childIt)->ProcessInput(event, target))
      return true;
  }
  return false;
}

template <class Derived>
struct ProcessInputBase {
  bool ProcessInputImpl(sf::Event event, const sf::RenderTarget& target) {
    return ProcessInputImplShared(
        static_cast<Derived*>(this)->GetChildren(), event, target);
  }
};

template <class Derived>
struct ProcessInputCommon {
  bool ProcessInputImpl(sf::Event event, const sf::RenderTarget& target) {
    return ProcessInputImplShared(
        static_cast<Derived*>(this)->children_, event, target);
  }
};

template <class Derived>
struct ProcessInputNull {
  bool ProcessInputImpl(sf::Event, const sf::RenderTarget&) {
    return false;
  }
};

}
}

#endif /* NEXUS_MIXINS_PROCESSINPUTCOMMON_HPP */
