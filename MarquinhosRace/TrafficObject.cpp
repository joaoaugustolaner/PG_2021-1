/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "TrafficObject.h"

TrafficObject::TrafficObject()
	: GameObject(), Stuck(true) { }

TrafficObject::TrafficObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(
		pos,
		size,
		sprite,
		glm::vec3(1.0f),
		glm::vec2(0.2f, 0.0f)),
	Stuck(true) { }

void TrafficObject::Move(TrafficObject* traffic)
{
	if (!traffic->Stuck) {
		traffic->Position.y += 0.2f;
		traffic->Position.y += 0.2f;

		if (traffic->Position.y >= 719.0f) {
			traffic->Position.y = -1000.0f - (rand() % 700 + 720);
		}
	}
}

void TrafficObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}