#ifndef NEXUS_PAGE_HPP
#define NEXUS_PAGE_HPP

#include "Nexus/Nexus.hpp"
#include "Nexus/MixIns/Contains.hpp"
#include "Nexus/MixIns/Draw.hpp"
#include "Nexus/MixIns/ProcessInput.hpp"
#include "Nexus/MixIns/SetOffset.hpp"
#include "Nexus/MixIns/SetOrigin.hpp"
#include "Nexus/MixIns/Update.hpp"

namespace nx {

template <class Derived>
class Page
  : public Nexus<Derived>,
    public mx::ContainsBase<Page<Derived>>,
    public mx::DrawBase<Page<Derived>>,
    public mx::ProcessInputBase<Page<Derived>>,
    public mx::SetOffsetBase<Page<Derived>>,
    public mx::SetOriginBase<Page<Derived>>,
    public mx::UpdateBase<Page<Derived>> {
  public:
    const std::vector<std::unique_ptr<INexus>>& GetChildren() const{
      return static_cast<const Derived*>(this)->children_;
    }
    std::vector<std::unique_ptr<INexus>>& GetChildren() {
      return static_cast<Derived*>(this)->children_;
    }
    const sf::Vector2f& GetOffset() const {
      return static_cast<const Derived*>(this)->offset_;
    }
    sf::Vector2f& GetOffset() {
      return static_cast<Derived*>(this)->offset_;
    }
    const sf::Vector2f& GetOrigin() const {
      return static_cast<const Derived*>(this)->origin_;
    }
    sf::Vector2f& GetOrigin() {
      return static_cast<Derived*>(this)->origin_;
    }
};

}

#endif /* PAGE_HPP */
