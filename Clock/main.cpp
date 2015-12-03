#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "const.h"

using namespace sf;
typedef struct TimeforClock
{
	int hour;
	int minute;
	int second;
};
typedef struct HandStuct
{
	RectangleShape second;
	RectangleShape minute;
	RectangleShape hour;
	CircleShape сentre;
};
void ClockNumber(RenderWindow& window)
{
	Font font;
	font.loadFromFile("D:/Универ/ИИП и игра/Clock/9329.ttf");
	Text number("", font, 50);
	number.setColor(Color::Black);
	number.setString("12");
	number.setPosition(235, 40);
	window.draw(number);
	number.setString("6");
	number.setPosition(240, 390);
	window.draw(number);
	number.setString("9");
	number.setPosition(60, 210);
	window.draw(number);
	number.setString("3");
	number.setPosition(420, 210);
	window.draw(number);

}
void InitializationHands(HandStuct& Hand)
{
	Hand.second.setSize(Vector2f(185, 3));
	Hand.second.setPosition(window_x / 2, window_x / 2);
	Hand.second.setFillColor(Color::Red);

	Hand.minute.setSize(Vector2f(140, 4));
	Hand.minute.setFillColor(Color::Black);
	Hand.minute.setPosition(window_x / 2, window_x / 2);

	Hand.hour.setSize(Vector2f(100, 6));
	Hand.hour.setFillColor((Color::Black));
	Hand.hour.setPosition(window_x / 2, window_x / 2);

	Hand.сentre.setRadius(10);
	Hand.сentre.setFillColor(sf::Color::Black);
	Hand.сentre.setPosition((window_x / 2) - Hand.сentre.getRadius(), (window_y / 2) - Hand.сentre.getRadius());
}
void DrawClock(RenderWindow& window, HandStuct Hand, CircleShape shape)
{
	window.draw(shape);
	ClockNumber(window);
	window.draw(Hand.hour);
	window.draw(Hand.minute);
	window.draw(Hand.second);
	window.draw(Hand.сentre);


}
void InputTime(TimeforClock& TimeClock)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	TimeClock.hour = st.wHour % 12;
	TimeClock.minute = st.wMinute;
	TimeClock.second = st.wSecond;

}
void AngleArrow(TimeforClock TimeClock, HandStuct& Hand)
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
	struct HandStuct Hand;
	struct TimeforClock TimeClock;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), "CLOCK", sf::Style::Default, settings);
	// Инициализация "круга" циферблата
	CircleShape shape(clock_face);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(8);
	shape.setOutlineColor(Color::Black);
	shape.setPointCount(4000);
	shape.setPosition((window_x /2) - shape.getRadius(), (window_y / 2) - shape.getRadius());
	// Инициализация стрелок часов
	InitializationHands(Hand);
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
		AngleArrow(TimeClock, Hand);
		DrawClock(window, Hand, shape);
		window.display();
	}
	return 0;
}