#include "ShivaApp.hpp"
#include "Gfx/Gfx.h"
#include <glm/glm.hpp>
#include "Core/Main.h"

OryolMain(ShivaApp)

AppState::Code ShivaApp::OnInit()
{
	Gfx::Setup(GfxSetup::Window(800, 600, "Shiva editor"));
	return App::OnInit();
}

AppState::Code ShivaApp::OnRunning()
{
	// render one frame
	Gfx::BeginPass(this->passAction);
	Gfx::EndPass();
	Gfx::CommitFrame();

	// update the clear color for next frame
	this->passAction.Color[0] += glm::vec4(0.01f, 0.005f, 0.0025f, 0.0f);
	this->passAction.Color[0] = glm::mod(this->passAction.Color[0], glm::vec4(1.0f));
	this->passAction.Color[0].w = 1.0f;

	// continue running or quit?
	return Gfx::QuitRequested() ? AppState::Cleanup : AppState::Running;
}

AppState::Code ShivaApp::OnCleanup()
{
	Gfx::Discard();
	return App::OnCleanup();
}
