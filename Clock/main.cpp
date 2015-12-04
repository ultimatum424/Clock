#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "const.h"
#define _USE_MATH_DEFINES
#include <math.h>



using namespace sf;
struct TimeforClock
{
	int hour;
	int minute;
	int second;
};
struct HandStuct
{
	RectangleShape second;
	RectangleShape minute;
	RectangleShape hour;
	CircleShape ñentre;
};
void SetPoints(RenderWindow& window, CircleShape& point)
{
	point.setFillColor(Color::Black);
	point.setPointCount(4000);
	for (int i = 1; i <= 60; i++)
	{
		point.setRadius(2);
		if (i % 5 == 0) point.setRadius(5);
		float x = WINDOW_X / 2 + (CLOCK_FACE - THICKNESS) * cos(i * 6 * float(M_PI) / 180) - 3 ;
		float y = WINDOW_X / 2 + (CLOCK_FACE - THICKNESS) * sin(i * 6 * float(M_PI) / 180) - 3;
		point.setPosition(x, y);
		window.draw(point);
	}
}
void InitializationHands(HandStuct& Hand)
{
	Hand.second.setSize(Vector2f(185, 3));
	Hand.second.setPosition(WINDOW_X / 2, WINDOW_Y / 2);
	Hand.second.setFillColor(Color::Red);

	Hand.minute.setSize(Vector2f(140, 4));
	Hand.minute.setFillColor(Color::Black);
	Hand.minute.setPosition(WINDOW_X / 2, WINDOW_Y / 2);

	Hand.hour.setSize(Vector2f(100, 5));
	Hand.hour.setFillColor((Color::Black));
	Hand.hour.setPosition(WINDOW_X / 2 + 1, WINDOW_Y / 2);

	Hand.ñentre.setRadius(10);
	Hand.ñentre.setFillColor(sf::Color::Black);
	Hand.ñentre.setPosition((WINDOW_X / 2) - Hand.ñentre.getRadius(), (WINDOW_Y / 2) - Hand.ñentre.getRadius());
}
void InitializationShape(CircleShape& shape)
{
	shape.setRadius(CLOCK_FACE);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(THICKNESS);
	shape.setOutlineColor(Color::Black);
	shape.setPointCount(4000);
	shape.setPosition((WINDOW_X / 2) - shape.getRadius(), (WINDOW_Y / 2) - shape.getRadius());
}
void DrawClock(RenderWindow& window, HandStuct Hand, CircleShape shape, CircleShape& point)
{
	window.draw(shape);
	SetPoints(window, point);
	window.draw(Hand.hour);
	window.draw(Hand.minute);
	window.draw(Hand.second);
	window.draw(Hand.ñentre);
}
void InputTime(TimeforClock& TimeClock)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	TimeClock.hour = st.wHour % 12;
	TimeClock.minute = st.wMinute;
	TimeClock.second = st.wSecond;

}
void RotationArrow(TimeforClock TimeClock, HandStuct& Hand)
{
	int angel;
	angel = 360 / 60 * TimeClock.second - 90;
	Hand.second.setRotation(angel);
	angel = (360 / 60 * TimeClock.minute) + TimeClock.second/ 10 - 90;
	Hand.minute.setRotation(angel);
	angel = ((360 / 12 * TimeClock.hour) + TimeClock.minute / 2 - 90);
	Hand.hour.setRotation(angel);
	
}

int main()
{
	HandStuct Hand;
	TimeforClock TimeClock;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "CLOCK", sf::Style::Default, settings);
	// Èíèöèàëèçàöèÿ "êðóãà" öèôåðáëàòà
	CircleShape shape;
	InitializationShape(shape);
	// Èíèöèàëèçàöèÿ ñòðåëîê ÷àñîâ
	InitializationHands(Hand);
	CircleShape point;
	
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				window.close();
		}
		InputTime(TimeClock);
		RotationArrow(TimeClock, Hand);
		DrawClock(window, Hand, shape, point);
		window.display();
	}
	return 0;
}