#include "Game.h"

Game::Game()
	:
	m_bDone(false)
{}

bool Game::isDone() const{
	return m_bDone;
}

void Game::setDone(bool bDone){
	m_bDone = bDone;
}