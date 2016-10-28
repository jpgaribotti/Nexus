#ifndef NEXUS_MIXINS_GETCHILDRENCOMMON_HPP
#define NEXUS_MIXINS_GETCHILDRENCOMMON_HPP

#include "Nexus/INexus.hpp"

namespace nx {
namespace mx {

template <class Derived>
struct GetChildrenCommon {
  RuntimeArray<INexus*> GetChildrenImpl() const {
    const auto& children = static_cast<const Derived*>(this)->children_;
    RuntimeArray<INexus*> out (children.size());
    std::transform(children.begin(), children.end(), out.begin(),
        [](const auto& child){ return child.get(); });
    return out;
  }
};

template <class Derived>
struct GetChildrenNull {
  RuntimeArray<INexus*> GetChildrenImpl() const {
    return { 0 };
  }
};

}
}

#endif /* NEXUS_MIXINS_GETCHILDRENCOMMON_HPP */
