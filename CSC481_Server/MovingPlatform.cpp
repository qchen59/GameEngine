#include "MovingPlatform.h"


 MovingPlatform::MovingPlatform() {
	 setSize(100, 100);
}

//sf::Vector2f MovingPlatform::update(Timeline* timline)
//{
//	float time = timline->getTime();
//	float elasped = time - lastTime;
//	lastTime = time;
//	sf::Vector2f p = rect.getPosition();
//	x = p.x;
//	if (Ticchanged) {
//		Ticchanged = false;
//	}
//	else {
//		// the time that to finish one turn
//		if (x >= 700.f) {
//			rect.setPosition(700, p.y);
//			flag = 1;
//		}
//		else if (x <= 0) {
//			rect.setPosition(0, p.y);
//			flag = 0;
//		}
//		if (flag == 0) {
//			rect.move(150.f * elasped, 0);
//		}
//		else if (flag == 1) {
//			rect.move(-150.f * elasped, 0);
//		}
//	}
//
//	return rect.getPosition();
//
//}
