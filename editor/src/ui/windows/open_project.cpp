#include "open_project.h"

#include "../common.h"
#include "../widgets/TitleIcon.h"
#include "../widgets/IconButton.h"

#include <imgui/imgui.h>

#include <filesystem>
#include <iostream>

#include "ui/widgets/ComboBox.h"
#include "ui/widgets/FileInput.h"

#include <nlohmann/json.hpp>
#include <fstream>

namespace fs = std::filesystem;

extern const char* backends[6];


static char nameBuffer[256] = "";
static char dirBuffer[256] = "";

typedef struct {
  ProjectTemplate template_;
  fs::path engine_path_;
}templates_t;
templates_t engineTemplates[1] =
{
{ Blank, "project_templates/blank" }
};


namespace editor
{
  OpenProject::OpenProject()
  {
    title = "Open Project";
  }

  void OpenProject::content()
  {
    TitleIcon("Open Project", GetImage("open_project64"));

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushFont(getFont("title"));
    ImGui::Text("New Project");

    ImGui::PopFont();
    ImGui::PushFont(getFont("std"));
    ImGui::TextColored(COLOR_DESC, "Select template : ");

    ImGui::BeginChild("ScrollBox", ImVec2(0, 154), true, ImGuiWindowFlags_HorizontalScrollbar);

    IconButton("Blank project", GetImage("blank512"));
    ImGui::SameLine();

    ImGui::EndChild();

    //parent directory input
    DirectoryInput(dirBuffer, 256, "Project Parent Directory", "C:/");


    //project name input
    ImGui::Text("Project Name");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::InputText("##NameInput", nameBuffer, 256);

    //graphics backend selection
    ComboBox("Graphics Backend", backends, 6);

    fs::path basePath = dirBuffer;
    fs::path folderName = nameBuffer;
    fs::path fullPath = basePath / folderName;
    bool baseExists = fs::exists(basePath);
    bool fullExists = fs::exists(fullPath);

    //on active que si c'est un path valide c'est a dire que le path complet n'existe pas et le path parent existe
    bool enabled = baseExists && fullExists;
    ImGui::BeginDisabled(enabled);
    if (ImGui::Button("Create Project"))
    {
      for (const auto& t : engineTemplates)
      {
        if (t.template_ == selected_template_)
        {
          try
          {
            // Copie tout le contenu récursivement
            fs::copy(GetExecutableDir()/t.engine_path_, fullPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            std::cout << "Dossier copié avec succès !\n";
          }
          catch (fs::filesystem_error& e)
          {
            std::cerr << "Erreur lors de la copie : " << e.what() << "\n";
          }
          break;
        }
      }
    }
    ImGui::EndDisabled();


    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PopFont();

    ImGui::PushFont(getFont("title"));
    ImGui::Text("Open Project");
    ImGui::PopFont();

    ImGui::PushFont(getFont("std"));

    //parser le fichier editor.json pour trouver les projets récents
    std::ifstream file("editor.json");
    if (!file.is_open())
    {
      throw std::runtime_error("Error while trying to open 'editor.json' file");
    }
    nlohmann::json json_object;
    file >> json_object;

    for (const nlohmann::json& p : json_object["recent-projects"])
    {
      std::string pstr = p;
      fs::path path = p;
      bool exists = fs::exists(path);
      if (!exists)
        ImGui::TextDisabled("%s", pstr.c_str());

      else if (ImGui::Button(pstr.c_str()))
        OpenProjectEditor(pstr.c_str());

      if (!exists && ImGui::IsItemHovered())
        ImGui::SetTooltip("Project does not exist anymore");
    }

    ImGui::PopFont();
  }
}
