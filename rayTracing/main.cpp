#include "common/CommonInterface.h"
#include "common/HiveCommonMicro.h"
#include "graphics/RenderEngineInterface.h"
#include "graphics/OpenGLEngineInterface.h"

int main(int, char**)
{
	try
	{
		hiveGLEngine::hiveInitOpenGLEngine();
		hiveRenderEngine::hiveRunEngine();
	}
	catch (...)
	{
		hiveCommon::hiveOutputWarning(__EXCEPTION_SITE__, "The program is terminated due to unexpected error.");
	}

	return 0;
}