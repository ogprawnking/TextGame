#include "GameObject.h"

class Food : public GameObject {
public:
	Food();
	Food(Point2D position);
	~Food() {};

	int getHP() { return m_healthPoints; }

	void draw();
	void drawDescription();
	void lookAt();
private:
	int m_healthPoints;

};