#include <Core/Core.h>
#include <Core/Logger.h>

#include <Core/Asserts.h>

int main(void)
{
	COREFATAL("Testing message: %f", 555.0f);
	COREERROR("Testing message: %f", 555.0f);
	COREWARNING("Testing message: %f", 555.0f);
	COREINFO("Testing message: %f", 555.0f);
	COREDEBUG("Testing message: %f", 555.0f);
	CORETRACE("Testing message: %f", 555.0f);

	COREASSERT(1 == 0);

	return 0;
}