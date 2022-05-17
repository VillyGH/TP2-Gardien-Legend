#pragma once
struct Inputs;
class Level01ContentManager;
class GameObject : public sf::Sprite
{
public:
	GameObject();
	GameObject(const GameObject& src);

	virtual void draw(sf::RenderWindow& window) const;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
	virtual bool init(const Level01ContentManager& manager);
	virtual bool update(float deltaT);
	virtual bool update(float deltaT, const Inputs& inputs);
	virtual void activate();
	virtual void deactivate();
	virtual bool isActive() const;
	virtual bool collidesWith(const GameObject& other) const;


	float getRotationAngleInRadians() const;
	void setRotationAngleRadians(const float angle);
	virtual void rotateInRadians(const float angle);

protected:
	float getAngleWith(const GameObject& other) const;
	bool active;
};

