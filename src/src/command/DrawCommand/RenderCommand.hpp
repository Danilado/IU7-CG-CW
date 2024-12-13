#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP

#include "DrawCommand.hpp"

class RenderCommand : public DrawCommand {
public:
  RenderCommand(double lightPitch, double lightYaw)
      : lightPitch(lightPitch), lightYaw(lightYaw) {}
  ~RenderCommand() = default;
  void exec() override;

private:
  double lightPitch = 0.;
  double lightYaw = 0.;
};

#endif
