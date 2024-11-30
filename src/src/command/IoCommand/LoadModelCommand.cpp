#include "LoadModelCommand.hpp"
#include "Cube.hpp"
#include "IoManager.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void LoadModelCommand::exec() {
  // IoManager &iom = Singleton<IoManager>::instance();
  SceneManager &sm = Singleton<SceneManager>::instance();

  // dst = sm.addObject(iom.loadObject(src));
  dst = sm.addObject(std::make_shared<Cube>(100));
}
