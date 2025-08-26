#pragma once
#include "Hsv.hpp"
#include <memory>
#include "Direction.hpp"
#include <OneButton.h>
#include "PlayerRenderer.hpp"

class Player
{
private:
	const double speedStep = 0.01;
	const double maxSpeed = 0.25;

	static std::string
	DirectionToString(const Direction &direction)
	{
		switch (direction)
		{
		case Direction::Left:
			return "Left";
		case Direction::Right:
			return "Right";
		case Direction::DoubleLeft:
			return "Double left";
		case Direction::DoubleRight:
			return "Double right";
		default:
			throw std::invalid_argument("Unexpected Direction");
		}
	}

	static void handleLeftClick(void *ctx)
	{
		auto *self = static_cast<Player *>(ctx);
		Serial.printf("%s => %s\n", DirectionToString(self->direction).c_str(), DirectionToString(Direction::Left).c_str());
		self->direction = Direction::Left;
	}

	static void handleDoubleLeftClick(void *ctx)
	{
		auto *self = static_cast<Player *>(ctx);
		Serial.printf("%s => %s\n", DirectionToString(self->direction).c_str(), DirectionToString(Direction::DoubleLeft).c_str());
		self->direction = Direction::DoubleLeft;
	}

	static void handleRightClick(void *ctx)
	{
		auto *self = static_cast<Player *>(ctx);
		Serial.printf("%s => %s\n", DirectionToString(self->direction).c_str(), DirectionToString(Direction::Right).c_str());
		self->direction = Direction::Right;
	}

	static void handleDoubleRightClick(void *ctx)
	{
		auto *self = static_cast<Player *>(ctx);
		Serial.printf("%s => %s\n", DirectionToString(self->direction).c_str(), DirectionToString(Direction::DoubleRight).c_str());
		self->direction = Direction::DoubleRight;
	}

public:
	double speed = 0.05;
	double position;
	Direction direction;
	Player(int pinBtnLeft,
		   int pinBtnRight)
	{
		position = 1.0;
		left = std::unique_ptr<OneButton>(new OneButton(pinBtnLeft));
		right = std::unique_ptr<OneButton>(new OneButton(pinBtnRight));
		left->attachClick(handleLeftClick, this);
		left->attachDoubleClick(handleDoubleLeftClick, this);
		left->setDebounceMs(1);
		left->setClickMs(150);

		right->attachClick(handleRightClick, this);
		right->attachDoubleClick(handleDoubleRightClick, this);
		right->setDebounceMs(1);
		right->setClickMs(150);

		renderer = std::unique_ptr<PlayerRenderer>(new PlayerRenderer());
		renderer->setup();
		direction = Direction::Right;
	};

	void move()
	{
		position = std::fmod(position + speed, NUM_LEDS);
	}

	void speedup()
	{
		if (speed >= maxSpeed)
		{
			speed = maxSpeed;
			return;
		}
		speed += speedStep;
	}

	int headIndex()
	{
		return static_cast<int>(position);
	}

	void show()
	{
		renderer->render(headIndex(), direction);
	}

	void tick()
	{
		auto previousDirection = this->direction;
		left->tick();
		right->tick();
		if (this->direction != previousDirection)
		{
			Serial.println("Redrawing player");
			show();
			FastLED.show();
		}
	}

private:
	std::unique_ptr<PlayerRenderer> renderer;
	std::unique_ptr<OneButton> left;
	std::unique_ptr<OneButton> right;
};
