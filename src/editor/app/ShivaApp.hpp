#pragma once

#include "Core/App.h"
#include "Gfx/GfxTypes.h"

using namespace Oryol;

class ShivaApp: public App
{
public:
    /// on init frame method
    AppState::Code OnInit() override;

    /// on running frame method
    AppState::Code OnRunning() override;

    /// on cleanup frame method
    AppState::Code OnCleanup() override;

	PassAction passAction;
};
