#pragma once

#define HORIZON_PLUGIN(plugin_) extern "C" { \
__declspec(dllexport) hge::IPlugin* LoadPlugin() { return new plugin_(); }}

namespace hge
{
	class IPlugin {
	public:
		IPlugin()=default;
		virtual ~IPlugin()=default;

		virtual void LoadAssets()=0;
		virtual void InitEditor()=0;
		virtual void InitRuntime()=0;
		virtual void Update()=0;
		virtual void ToolbarStructure()=0;
	};
}