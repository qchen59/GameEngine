#include "Platform.h"


Platform::Platform() {


}

void Platform::trans(float a, float b) {
	rect.setSize(sf::Vector2f(a, b));
}
