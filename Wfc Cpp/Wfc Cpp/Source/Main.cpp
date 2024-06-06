#include "Engine/Engine.h"
#include "Demo/WfcDemo.h"

using namespace Satellite;

int main(int argc, char* args[])
{
	Engine* engine = Engine::Instance();

	Game* game = new Demo::WfcDemo();

	engine->Start(game);
	engine->Run();
	engine->Destroy();

	delete game;

	return 0;
}