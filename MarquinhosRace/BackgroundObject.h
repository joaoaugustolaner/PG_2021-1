/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef BACKGROUNDOBJECT_H
#define BACKGROUNDOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class BackgroundObject : public GameObject
{
public:
	GLboolean Stuck;

	BackgroundObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);

	void Move(BackgroundObject *background);

	void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif