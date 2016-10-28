#ifndef NEXUS_MIXINS_UPDATECOMMON_HPP
#define NEXUS_MIXINS_UPDATECOMMON_HPP

namespace nx {
namespace mx {

template <class Container>
void UpdateImplShared(const Container& children) {
  for (const auto& child : children) {
    child->Update();
  }
}

template <class Derived>
struct UpdateBase {
  void UpdateImpl() {
    UpdateImplShared(static_cast<const Derived*>(this)->GetChildren());
  }
};

template <class Derived>
struct UpdateCommon {
  void UpdateImpl() {
    UpdateImplShared(static_cast<const Derived*>(this)->children_);
  }
};

template <class Derived>
struct UpdateNull {
  void UpdateImpl() {}
};

}
}

#endif /* NEXUS_MIXINS_UPDATECOMMON_HPP */
