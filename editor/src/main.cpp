#include <hge/core/engine.h>
#include <hge/core/private/engine_backend.h>
#include <hge/core/window.h>
#include <hge/filesystem/filesystem.h>
#include <hge/filesystem/ini_parser.h>
#include <hge/core/common.h>
#include <hge/core/log.h>

#include <hrl/hrl.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "ui/common.h"
#include "ui/style.h"
#include "ui/menu_bar.h"

#include "ui/windows/open_project.h"
#include "ui/windows/project_configuration.h"
#include "ui/windows/script_editor.h"
#include "ui/windows/content_browser.h"
#include "ui/windows/texture_editor.h"
#include "ui/windows/viewport.h"
#include "ui/windows/place_actors.h"

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
	std::string imageData = HGE_filesystem::HGE_GetFileContent(_path, &imageSize, true);

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

	HGE_InitEngine(HGE_PREVIEW, "config.ini", (void*)glfwGetProcAddress, 0);
	game_scene = HGE_GetEngineHRL_SceneID();

	//Test
	size_t texSize;
	std::string texString = HGE_filesystem::HGE_GetFileContent("canada.jpg", &texSize, true);
	size_t normalSize;
	std::string normalString = HGE_filesystem::HGE_GetFileContent("normal.jpg", &normalSize, true);
	//crée la texture et le material
	HRL_id tex = HRL_CreateTexture(texString.c_str(), texSize);
	HRL_id normaltex = HRL_CreateTexture(normalString.c_str(), normalSize);
	//material
	HRL_id mat = HRL_CreateMaterial(HRL_SpriteShader);
	HRL_MaterialSetTexture(mat, HRL_T_Albedo, tex);
	HRL_MaterialSetTexture(mat, HRL_T_Normal, normaltex);
	HRL_MaterialSetFloat(mat, "NormalStrength", 1);

	//mesh 1 : canada flag
	HRL_id sprite = HRL_CreateMesh(game_scene, HRL_Sprite);
	HRL_SetMeshMaterial(sprite, mat);
	HRL_SetMeshScale(sprite, 10, 10, 10);

	//Lights
	HGE_Vec3 lightpos(0.f, 0.f, 0.f);
	HRL_id light0 = HRL_CreateLight(game_scene, HRL_PointLight);
	HRL_SetLightAttenuation(light0, 0.02f);
	HRL_SetLightIntensity(light0, 5.f);
	HRL_SetLightColor(light0, 1.f, 1.f, 1.f);
	HRL_SetLightRotation(light0, 0.f, 0.f, 0.f);


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
	editor::AddImage("generic-actor64", "images/generic-actor64.png");

	//Windows
	editor::AddWindow("OpenProject", EDITOR_WIN(editor::OpenProject,));
	editor::AddWindow("ProjectConfiguration", EDITOR_WIN(editor::ProjectConfiguration,));
	editor::AddWindow("ScriptEditor", EDITOR_WIN(editor::ScriptEditor,));
	editor::AddWindow("ContentBrowser", EDITOR_WIN(editor::ContentBrowser,));
	editor::AddWindow("TextureEditor", EDITOR_WIN(editor::TextureEditor,));
	editor::AddWindow("Viewport", EDITOR_WIN(editor::Viewport, game_scene));
	editor::AddWindow("PlaceActors", EDITOR_WIN(editor::PlaceActors,));

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


	while (HGE_EngineRunning())
	{
		if (glfwWindowShouldClose(mainWin))
		{
			HGE_QuitEngine();
		}

		HGE_UpdateEngine(1/180.f, 0);

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

		const float footer_height = ImGui::GetFrameHeightWithSpacing();

		// Créer le dockspace
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

	SaveWindowState();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}