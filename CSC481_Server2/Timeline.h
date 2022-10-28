#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Timeline
{
private:
	// The time of the anchor at start
	float start_time;
	// step size (inverse of speed)
	float tic;
	bool isPaused;
	// Anchor time at last pause
	float last_paused_time;
	// How much anchor time this timelie has been paused
	float elapsed_pause_time = 0.f;
	// Could be a system library or an instance of timeline
	Timeline* anchor;
	// Whether this timeline is the original timeline
	bool ori;
	// The clock to track time
	sf::Clock* clock;
public:
	Timeline(Timeline* anchor, float tic, bool ori, sf::Clock* clock);
	float getTime();
	void paused();
	void unpaused();
	void changeTic(float new_tic);
};

