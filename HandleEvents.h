#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Judge.h"

class HandleEvents : protected Judge {
public:
	void events();
};
