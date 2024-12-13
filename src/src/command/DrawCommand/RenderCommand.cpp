#include "RenderCommand.hpp"
#include "DrawManager.hpp"
#include "SingletonTemplate.hpp"

void RenderCommand::exec() {
  DrawManager &dm = Singleton<DrawManager>::instance();
  dm.clear();
  dm.renderScene(lightYaw, lightPitch);
}
