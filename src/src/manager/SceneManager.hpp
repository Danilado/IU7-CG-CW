#ifndef BASE_MANAGER_HPP
#define BASE_MANAGER_HPP

#include "Scene.hpp"
#include <memory>

class SceneManager {
private:
  std::shared_ptr<Scene> scene;

public:
  SceneManager();
  ~SceneManager() = default;

  std::shared_ptr<Scene> getScene(void) const;
  void setScene(const std::shared_ptr<Scene> &src);
  size_t addObject(ObjectPtr obj);
  bool removeObject(size_t id);
  void resetScene();

  SceneManager(const SceneManager &) = delete;
  SceneManager &operator=(const SceneManager &) = delete;
};

#endif
