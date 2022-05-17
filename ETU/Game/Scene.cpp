#include "stdafx.h"
#include "Scene.h"

SceneResult Scene::result;

Scene::Scene(SceneType type)
	: sceneType(type)
{

}

Scene::~Scene()
{

}

void Scene::pause()
{

}

void Scene::unPause()
{

}

bool Scene::handleEvents(sf::RenderWindow& window)
{
	bool retval = false;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			retval = true;
		}
	}
	return retval;
}

SceneType Scene::getSceneType() const
{
	return sceneType;
}

SceneResult Scene::getSceneResult() const
{
	return result;
}