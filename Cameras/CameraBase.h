#pragma once
#include "../Objects/GameActor.h"

class CameraBase : public GameActor {
public:
	CameraBase(Game* game)
		: GameActor(game)
	{}

protected:
	void SetViewMatrix(const mat4& mat);
};