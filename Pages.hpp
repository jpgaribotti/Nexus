#ifndef NEXUS_PAGES_HPP
#define NEXUS_PAGES_HPP

#include "Nexus/Nexus.hpp"

#include <memory>

namespace nx {

template <int numPages>
class Pages : public Nexus<Pages<numPages>> {
  friend class Nexus<Pages<numPages>>;
  public:
    int GetCurrent() const;
    void SetCurrent(int id);
    void SetPage(int id, std::unique_ptr<INexus> page);

  protected:
    bool ContainsImpl(sf::Vector2f pos) const;
    void DrawImpl(sf::RenderTarget& target) const;
    bool ProcessInputImpl(sf::Event event, const sf::RenderTarget& target);
    void SetOffsetImpl(sf::Vector2f pos);
    void SetOriginImpl(sf::Vector2f pos);
    void UpdateImpl();

    std::unique_ptr<INexus> pages_[numPages];
    int id_;
};

template <int numPages>
int Pages<numPages>::GetCurrent() const {
  return id_;
}

template <int numPages>
void Pages<numPages>::SetCurrent(int id) {
  id_ = id;
}

template <int numPages>
void Pages<numPages>::SetPage(int id, std::unique_ptr<INexus> page) {
  pages_[id] = std::move(page);
}

template <int numPages>
bool Pages<numPages>::ContainsImpl(sf::Vector2f pos) const {
  return pages_[id_]->Contains(pos);
}

template <int numPages>
void Pages<numPages>::DrawImpl(sf::RenderTarget& target) const {
  pages_[id_]->Draw(target);
}

template <int numPages>
bool Pages<numPages>::ProcessInputImpl(
    sf::Event event, const sf::RenderTarget& target) {
  return pages_[id_]->ProcessInput(event, target);
}

template <int numPages>
void Pages<numPages>::SetOffsetImpl(sf::Vector2f) {}

template <int numPages>
void Pages<numPages>::SetOriginImpl(sf::Vector2f pos) {
  pages_[id_]->SetOrigin(pos);
}

template <int numPages>
void Pages<numPages>::UpdateImpl() {
  pages_[id_]->Update();
}

}

#endif /* NEXUS_PAGES_HPP */
