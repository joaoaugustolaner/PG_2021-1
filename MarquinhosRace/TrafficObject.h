/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef TRAFFITOBJECT_H
#define TRAFFICOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class TrafficObject : public GameObject
{
public:
	GLboolean Stuck;

	TrafficObject();
	TrafficObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);

	void      Move(TrafficObject *traffic);
	void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif