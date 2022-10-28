#include "Timeline.h"

Timeline::Timeline(Timeline* anchor, float tic, bool ori, sf::Clock* clock)
{
	this->anchor = anchor;
	this->tic = tic;
	this->isPaused = false;
	this->ori = ori;
	this->clock = clock;
	this->start_time = clock->getElapsedTime().asSeconds();
}

float Timeline::getTime()
{
	if (ori) {
		// If is the timline that repersent the real time, return the real time
		float time = clock->getElapsedTime().asSeconds();
		return time;
	}
	else {
		// not paused
		if (!isPaused) {
			float ct = anchor->getTime();
			// ct is the current time, get the elapsed based on the real time and the start time
			float elapsed = ct - start_time;
			// minus the elapsed pause time
			elapsed -= elapsed_pause_time;
			return elapsed / tic;
		} // paused
		else {
			float ct = last_paused_time;
			float elapsed = ct - start_time;
			elapsed -= elapsed_pause_time;
			return elapsed / tic;
		}
	}

}

void Timeline::paused()
{
	last_paused_time = anchor->getTime();
	//	std::cout << last_paused_time << std::endl;
	isPaused = true;
}

void Timeline::unpaused()
{
	elapsed_pause_time += anchor->getTime() - last_paused_time;
	//	std::cout << elapsed_pause_time << std::endl;
	isPaused = false;
}

void Timeline::changeTic(float new_tic)
{
	tic = new_tic;
}