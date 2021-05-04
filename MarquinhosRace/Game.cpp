/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "TrafficObject.h"
#include "BackgroundObject.h"

SpriteRenderer* Renderer;
SpriteRenderer* RendererPlayer;

BackgroundObject* Background1;
BackgroundObject* Background2;
PlayerObject* Player;

TrafficObject* Minivan1;
TrafficObject* Minivan2;
TrafficObject* AudiB;
TrafficObject* AudiC;

GameObject* GameOver;
GameObject* StartGame;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("textures/road.png", GL_TRUE, "background");

	ResourceManager::LoadTexture("textures/audi.png", GL_TRUE, "audi");
	ResourceManager::LoadTexture("textures/minivan.png", GL_TRUE, "minivan");
	ResourceManager::LoadTexture("textures/audib.png", GL_TRUE, "audib");
	ResourceManager::LoadTexture("textures/audic.png", GL_TRUE, "audic");

	ResourceManager::LoadTexture("textures/gameover.png", GL_TRUE, "GameOver");
	ResourceManager::LoadTexture("textures/startscreen.png", GL_TRUE, "StartGame");

	Shader shader1 = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader1);

	glm::vec2 playerPos = glm::vec2(500, 490);
	Player = new PlayerObject(playerPos, glm::vec2(105, 222), ResourceManager::GetTexture("audi"));

	glm::vec2 GameOverPos = glm::vec2(1280, 0);
	GameOver = new GameObject(GameOverPos, glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("GameOver"));

	glm::vec2 StartGamePos = glm::vec2(0, 0);
	StartGame = new GameObject(StartGamePos, glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("StartGame"));

	glm::vec2 background1Pos = glm::vec2(0, 0);
	Background1 = new BackgroundObject(background1Pos, glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("background"));

	glm::vec2 background2Pos = glm::vec2(0, -720);
	Background2 = new BackgroundObject(background2Pos, glm::vec2((this->Width), (this->Height)), ResourceManager::GetTexture("background"));

	glm::vec2 minivan = glm::vec2(700, -5000);
	Minivan1 = new TrafficObject(minivan, glm::vec2(80, 202), ResourceManager::GetTexture("minivan"));

	glm::vec2 audib = glm::vec2(880, -800);
	AudiB = new TrafficObject(audib, glm::vec2(105, 222), ResourceManager::GetTexture("audib"));

	glm::vec2 audic = glm::vec2(290, -1400);
	AudiC = new TrafficObject(audic, glm::vec2(105, 222), ResourceManager::GetTexture("audic"));

	glm::vec2 minivan2 = glm::vec2(500, -3000);
	Minivan2 = new TrafficObject(minivan2, glm::vec2(80, 202), ResourceManager::GetTexture("minivan"));
}

void Game::Update(GLfloat dt)
{
	Background1->Move(Background1);
	Background2->Move(Background2);

	Minivan1->Move(Minivan1);
	Minivan2->Move(Minivan2);
	AudiB->Move(AudiB);
	AudiC->Move(AudiC);

	this->DoCollisions();

	if (this->State == GAME_OVER)
	{
		GameOver->Displayed = true;
		GameOver->Position.x = 0.0f;
	}
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->Keys[GLFW_KEY_SPACE] and this->State == GAME_OVER) {
		this->Init();
		this->State = GAME_ACTIVE;
	}

	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;

		if (this->Keys[GLFW_KEY_SPACE]) {

			StartGame->Position.x = 1280;
			Player->Stuck = false;
			Background1->Stuck = false;
			Background2->Stuck = false;
			Minivan1->Stuck = false;
			AudiB->Stuck = false;
			AudiC->Stuck = false;
			Minivan2->Stuck = false;
		}

		if (!Player->Stuck) {
			if (this->Keys[GLFW_KEY_A])
			{
				Player->Position.x -= 1.0f;

				if (Player->Position.x <= 250)
					Player->Position.x = 250;
			}
			else if (this->Keys[GLFW_KEY_D])
			{
				Player->Position.x += 1.0f;

				if (Player->Position.x >= 930)
					Player->Position.x = 930;
			}
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Shader shader1 = ResourceManager::GetShader("sprite");

		Background1->Draw(*Renderer, 0.1f);
		Background2->Draw(*Renderer, 0.1f);

		Player->Draw(*Renderer, 0.2f);

		Minivan1->Draw(*Renderer, 0.02f);
		Minivan2->Draw(*Renderer, 0.02f);
		AudiB->Draw(*Renderer, 0.02f);
		AudiC->Draw(*Renderer, 0.02f);

		StartGame->Draw(*Renderer, 0.02f);
	}
	else if (this->State == GAME_OVER)
	{
		GameOver->Draw(*Renderer, 0.02f);
		GameOver->Position.x = 0.0f;
	}
}

void Game::DoCollisions()
{
	if (CheckCollision(*Player, *Minivan1))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Minivan2))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *AudiB))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *AudiC))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
}

GLboolean Game::CheckCollision(GameObject& one, GameObject& two)
{
	GLboolean collisionX = (one.Position.x >= two.Position.x && one.Position.x <= (two.Position.x + two.Size.x)) ||
		((one.Position.x + one.Size.x) >= two.Position.x && (one.Position.x + one.Size.x) <= (two.Position.x + two.Size.x));

	GLboolean collisionY = (one.Position.y >= two.Position.y && one.Position.y <= (two.Position.y + two.Size.y)) ||
		((one.Position.y + one.Size.y) >= two.Position.y && (one.Position.y + one.Size.y) <= (two.Position.y + two.Size.y));

	return collisionX && collisionY;
}