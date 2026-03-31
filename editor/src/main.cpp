#include <hge/core/engine.h>
#include <hge/filesystem/filesystem.h>
#include <hge/filesystem/ini_parser.h>
#include <hge/core/common.h>
#include <hge/core/log.h>
#include <hge/core/actor.h>
#include <hge/std/std_module.h>

#include <hrl/hrl.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

//déja fait dans hrl.dll, mais on doit le refaire dans editor.exe
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ui/common.h"
#include "ui/style.h"
#include "ui/menu_bar.h"
#include "ui/toolbar.h"

#include "ui/windows/open_project.h"
#include "ui/windows/project_configuration.h"
#include "ui/windows/script_editor.h"
#include "ui/windows/content_browser.h"
#include "ui/windows/texture_editor.h"
#include "ui/windows/viewport.h"
#include "ui/windows/place_actors.h"
#include "ui/windows/outliner.h"
#include "ui/windows/actor_details.h"

#include <memory>
#include <string>

GLFWwindow* mainWin;
HRL_id game_scene;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	HRL_WindowResizeCallback(width, height);
}

void SetWindowIcon(GLFWwindow* _win, const char* _path)
{
	size_t imageSize;
	std::string imageData = hge::filesystem::GetFileContent(_path, &imageSize, true);

	//si l'image ou la taille est invalide
	if (imageData.empty() || imageSize == 0)
	{
		LOG_ERROR("Window set icon failed: error while reading image of size : " + std::to_string(imageSize) + "o");
		return;
	}

	//on charge l'image avec stb, puis on change l'icone glfw
	int w, h, channels;
	unsigned char* pixels = stbi_load_from_memory(
		(stbi_uc*)imageData.c_str(),
		(int)imageSize,
		&w,
		&h,
		&channels,
		STBI_rgb_alpha);

	//on arrete si les pixels sont vides
	if (!pixels)
	{
		std::string failure = stbi_failure_reason();
		LOG_ERROR("Window set icon failed: error while reading image pixels" + failure);
		return;
	}

	//on crée l'objet image de glfw
	GLFWimage icon;
	icon.width = w;
	icon.height = h;
	icon.pixels = pixels;
	glfwSetWindowIcon(_win, 1, &icon);

	//on libere la mémoire allouée a stb
	stbi_image_free(pixels);
}

void SaveWindowState()
{
	for (const auto& [key, w] : editor::GetWindows())
	{
		editor::GetConfigIni("wins")->SetKeyValue(key.c_str(), w->visible);
	}
	editor::GetConfigIni("wins")->SaveIniFile();
}

int main(int argc, char** argv)
{
	glfwInit();
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	mainWin = glfwCreateWindow(1600, 1080, "Editor", nullptr, nullptr);
	SetWindowIcon(mainWin, "images/hge.png");
	glfwSetFramebufferSizeCallback(mainWin, framebuffer_size_callback);
	glfwMakeContextCurrent(mainWin);

	//glfwSwapInterval(0);

	hge::InitEngine(HGE_PREVIEW, "config.ini", (void*)glfwGetProcAddress, false);
	game_scene = hge::GetEngineHRL_SceneID();


	//important pour les chemins de fichiers
	editor::argv = argv;

	/** ImGui **/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	//enable docking
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	//sauvegarder et charger le layout des fenêtres
	io.IniFilename = "editor_layout.ini";

	//style
	ImGui::StyleColorsClassic();
	editor::applyStyle();


	//contexte glfw et gl3
	ImGui_ImplGlfw_InitForOpenGL(mainWin, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	/** Ressources */
	//Fonts
	editor::addFont("std", "fonts/Inter_18pt-Regular.ttf", 20);
	editor::addFont("title", "fonts/Inter_18pt-Regular.ttf", 32);
	editor::addFont("desc", "fonts/Inter_18pt-Regular.ttf", 16);
	editor::addFont("cascadia-code", "fonts/CascadiaCode-Medium.ttf", 32);

	//Images
	editor::AddImage("windows64", "images/windows64.png");
	editor::AddImage("linux64", "images/linux64.png");
	editor::AddImage("apple64", "images/apple64.png");
	editor::AddImage("arrow_right16", "images/arrow-right16.png");
	editor::AddImage("gear64", "images/gear64.png");
	editor::AddImage("gear128", "images/gear128.png");
	editor::AddImage("open_project64", "images/open-project64.png");
	editor::AddImage("blank512", "images/blank512.png");
	editor::AddImage("folder128", "images/folder128.png");
	editor::AddImage("generic-file128", "images/generic-file128.png");
	editor::AddImage("hs-file128", "images/hs-file128.png");
	editor::AddImage("img-file128", "images/img-file128.png");
	editor::AddImage("mat-file128", "images/mat-file128.png");
	editor::AddImage("sound-file128", "images/sound-file128.png");
	editor::AddImage("media-file128", "images/media-file128.png");
	editor::AddImage("scene-file128", "images/scene-file128.png");
	editor::AddImage("generic-actor64", "images/generic-actor64.png");
	editor::AddImage("build64", "images/build64.png");
	editor::AddImage("play64", "images/play64.png");
	editor::AddImage("save64", "images/save64.png");
	editor::AddImage("reload64", "images/reload64.png");

	//Windows
	editor::AddWindow("OpenProject", EDITOR_WIN(editor::OpenProject,));
	editor::AddWindow("ProjectConfiguration", EDITOR_WIN(editor::ProjectConfiguration,));
	editor::AddWindow("ScriptEditor", EDITOR_WIN(editor::ScriptEditor,));
	editor::AddWindow("ContentBrowser", EDITOR_WIN(editor::ContentBrowser,));
	editor::AddWindow("TextureEditor", EDITOR_WIN(editor::TextureEditor,));
	editor::AddWindow("Viewport", EDITOR_WIN(editor::Viewport, game_scene));
	editor::AddWindow("PlaceActors", EDITOR_WIN(editor::PlaceActors,));
	editor::AddWindow("Outliner", EDITOR_WIN(editor::Outliner,));
	editor::AddWindow("ActorDetails", EDITOR_WIN(editor::ActorDetails,));

	//Ini config files
	editor::AddConfigIni("wins", "wins.ini");

	//on rend visible toutes les windows qui l'etaient à la dernier sauvegarde
	for (const auto& [key, value] : editor::GetConfigIni("wins")->GetEntries<int>())
	{
		auto* win_ = editor::GetWindow(key.c_str());
		if (win_)
		{
			win_->visible = value;
		}
	}


	while (hge::EngineRunning())
	{
		if (glfwWindowShouldClose(mainWin))
		{
			hge::QuitEngine();
		}

		hge::UpdateEngine(1/180.f, editor::update_physics);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

		//Window principale de dock
		ImGui::SetNextWindowPos(ImVec2(0,0));
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::Begin("DockSpace Window", nullptr, window_flags);

		//Toolbar
		editor::ShowToolbar();

		const float footer_height = ImGui::GetFrameHeightWithSpacing();

		//Créer le dockspace
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(
		dockspace_id,
		ImVec2(0.0f, -footer_height),
		ImGuiDockNodeFlags_None
		);

		editor::ShowMenuBar();

		for (const auto& [name, w] : editor::GetWindows())
		{
			w->Show(1/180.f);
		}

		//pied de page avec le status et fps
		ImGui::Separator();
		char bufferStatus[64];
		snprintf(bufferStatus, sizeof(bufferStatus), "Ready | FPS: %.0f", ImGui::GetIO().Framerate);
		float text_width = ImGui::CalcTextSize(bufferStatus).x;
		ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - text_width);
		ImGui::TextDisabled(bufferStatus);


		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(mainWin);
		glfwPollEvents();
	}

	editor::selected_actors_.clear();

	SaveWindowState();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}