#include "Shoot.h"
#include "Fire.h"

Shoot::Shoot() {
	for (int i = 0; i <= 4; i++) {
		MovingPlatform ship;
		ship.setPosition(50+200*i,0);
		sl.push_back(ship);
	}

	for (int i = 0; i <= 4; i++) {
		MovingPlatform ship;
		ship.setPosition(50 + 200 * i, 100);
		sl.push_back(ship);
	}
}

void Shoot::shoot(GameObject* go, sf::RenderWindow* wd) {
	if (go->getFocus()) {
		if (p == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			p = true;

		}

		if (p == true) {
			p = false;
			Fire f;
			f.setPosition(go->getShape().getPosition().x + 25, go->getShape().getPosition().y);
			fl.push_back(f);
		}
	}

}

void Shoot::update(GameObject* go , sf::RenderWindow* wd) {


	for (auto& f : fl)
	{
		f.updateShape(0, -150.f * go->getTime());
		wd->draw(f.getShape());
	}

	for (auto& s : sl)
	{
		s.updateShape(0, 50.f * go->getTime());
		wd->draw(s.getShape());
	}

	// check collision between fire and ship
	for (auto& f : fl)
	{
		for (auto& s : sl) {
			if (cld.collision(&f, &s)) {
				//std::cout << "Shoot!" << std::endl;
				//s.updateColor(0, 0, 0);
				s.setPosition(1000, 1000);
				//sl.remove(s);
			}
		}
	}

	//std::list<GameObject>::iterator fi = fl.begin();
	//while (fi != fl.end()) {
	//	std::list<GameObject>::iterator si = sl.begin();
	//	bool remove = false;
	//	while (si != sl.end()) {
	//		if (cld.collision(&*fi, &*si)) {
	//			std::cout << "collision!" << std::endl;
	//			fi = fl.erase(fi);
	//			si = sl.erase(si);
	//			remove = true;
	//		}
	//		else {
	//			si++;
	//		}
	//	}
	//	if (remove == false) {
	//	fi++;
	//	}
	//}


}
