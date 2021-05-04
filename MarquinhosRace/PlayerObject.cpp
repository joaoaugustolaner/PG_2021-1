/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "PlayerObject.h"

PlayerObject::PlayerObject()
	: GameObject(), Stuck(true) { }

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,                   
		size,							
		sprite,                         
		glm::vec3(1.0f),                
		glm::vec2(0.0f, 0.0f)),         
	Stuck(true) { }

void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}