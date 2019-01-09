#pragma once

#include "GridObject.h"

class Exit : public GridObject
	
{
	
public:
	Exit();

	void Collide(GameObject& _collider);

private:


};