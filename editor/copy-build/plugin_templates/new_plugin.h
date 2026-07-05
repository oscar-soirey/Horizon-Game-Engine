#pragma once

#include <plugins/iplugin.h>

class NewPlugin : public hge::IPlugin {
public:
	void LoadAssets() override;
	void InitEditor() override;
	void InitRuntime() override;
	void Update() override;
	void ToolbarStructure() override;
};
HORIZON_PLUGIN(NewPlugin);