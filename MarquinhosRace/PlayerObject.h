/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class PlayerObject : public GameObject
{
public:
	GLboolean Stuck = true;

	PlayerObject();
	PlayerObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
	PlayerObject(glm::vec2 pos, Texture2D sprite, glm::vec2 posTexture);

	glm::vec2 Move(GLfloat dt, GLuint window_width);

	void Reset(glm::vec2 position, glm::vec2 velocity);
	GLint ControleMovimento = 0;
	GLfloat TexturePosX = 1.0f / 3.0f;
};

#endif