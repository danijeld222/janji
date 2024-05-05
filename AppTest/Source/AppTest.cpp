#include <Core/Core.h>
#include <Core/Logger.h>
#include <Core/Asserts.h>

#include "Game.h"

int main(void)
{
    // NOTE - Dani:
    // We bind to create game method which will be called from Core
    // This is not the best way to do this, there is a way with extern method that is 
    // declared in Core and defined here but there is a problem with curcular dependency.
    // If we find a solution to do it way as described above int main(void) then should
    // be moved to Core.
    //
    // https://stackoverflow.com/questions/78431974/calling-extern-function-from-dll-declared-in-exe-error-lnk2019-unresolved
    //

    CreateGame = CreateGameImplementation;

    return CoreMain();
}