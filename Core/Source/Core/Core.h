#pragma once

#include "Defines.h"
#include "Logger.h"
#include "GameType.h"

#include <functional>

// First we should bind function with same signature in application then call CoreMain()
COREAPI std::function<b8(Game* GameOut)> CreateGame;

// This is called from int main(void) of application binded to this dll
COREAPI int CoreMain();