#include "ShiryuTeam/Application.h"
#include "ShiryuTeam/EntryPoint.h"

#include "ShiryuTeam/Image.h"
#include "ShiryuTeam/UI/UI.h"

#include <string>
#include <vector>
#include <functional>

namespace ShiryuTeam {

struct AppInfo
{
    std::string id;
    std::string name;
    std::string description;
    std::string category;
    std::string iconPath;
    bool installed = false;
    bool featured = false;
};

class LauncherLayer : public Layer
{
public:
    LauncherLayer()
    {
        m_Apps = {
            {"shiryu-dev", "Shiryu Dev", "Development environment with AI assistance", "Development", "", true, true},
            {"shiryu-projects", "Shiryu Projects", "Project and task management", "Productivity", "", true, true},
            {"shiryu-cloud", "Shiryu Cloud", "Manage Cloudflare deployments", "DevOps", "", false, true},
            {"shiryu-teams", "Shiryu Teams", "Team collaboration and chat", "Communication", "", false, true},
        };
    }

    virtual void OnUIRender() override
    {
        if (!m_IsLoggedIn)
        {
            RenderLoginScreen();
        }
        else
        {
            RenderMainLayout();
        }
    }

private:
    void RenderLoginScreen()
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);

        auto image = Application::Get().GetApplicationIcon();
        if (image)
        {
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 64) * 0.5f);
            ImGui::Image(image->GetDescriptorSet(), { 64, 64 });
        }

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
        
        ImGui::Text("Shiryu.Launcher");
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Sign in to your account");

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 300) * 0.5f);
        ImGui::PushItemWidth(300);
        ImGui::InputText("##email", m_EmailBuffer, sizeof(m_EmailBuffer), ImGuiInputTextFlags_None);
        ImGui::PopItemWidth();

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 300) * 0.5f);
        ImGui::PushItemWidth(300);
        ImGui::InputText("##password", m_PasswordBuffer, sizeof(m_PasswordBuffer), ImGuiInputTextFlags_Password);
        ImGui::PopItemWidth();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
        
        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            m_LoginClicked = true;
        }

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5f);
        if (UI::ButtonCentered("Sign In"))
        {
            m_IsLoggedIn = true;
        }

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) * 0.5f);
        ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.8f, 1.0f), "Create Account");

        ImGui::End();
    }

    void RenderMainLayout()
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);

        RenderSidebar();

        ImGui::SameLine();
        
        if (m_CurrentPage == "home")
            RenderHomePage();
        else if (m_CurrentPage == "apps")
            RenderAppsPage();
        else if (m_CurrentPage == "installed")
            RenderInstalledPage();
        else if (m_CurrentPage == "settings")
            RenderSettingsPage();

        ImGui::End();
    }

    void RenderSidebar()
    {
        ImGui::BeginChild("Sidebar", { 220, ImGui::GetIO().DisplaySize.y }, true);
        
        auto image = Application::Get().GetApplicationIcon();
        if (image)
        {
            ImGui::Image(image->GetDescriptorSet(), { 32, 32 });
            ImGui::SameLine();
            ImGui::Text("Shiryu");
        }

        ImGui::Separator();

        if (ImGui::Button("Home"))
            m_CurrentPage = "home";
        
        if (ImGui::Button("Browse Apps"))
            m_CurrentPage = "apps";
        
        if (ImGui::Button("Installed"))
            m_CurrentPage = "installed";

        ImGui::Separator();

        if (ImGui::Button("Settings"))
            m_CurrentPage = "settings";

        ImGui::Separator();
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), m_UserEmail.c_str());
        
        if (ImGui::Button("Logout"))
        {
            m_IsLoggedIn = false;
            m_UserEmail = "";
        }

        ImGui::EndChild();
    }

    void RenderHomePage()
    {
        ImGui::BeginChild("Content", { ImGui::GetIO().DisplaySize.x - 220, ImGui::GetIO().DisplaySize.y });
        
        ImGui::SetCursorPos({ 20, 20 });
        ImGui::Text("Welcome back!");
        
        ImGui::SetCursorPos({ 20, 60 });
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Your apps");
        
        ImGui::SetCursorPos({ 20, 90 });
        for (const auto& app : m_Apps)
        {
            if (app.installed)
            {
                RenderAppCard(app, true);
            }
        }

        ImGui::EndChild();
    }

    void RenderAppsPage()
    {
        ImGui::BeginChild("AppsContent", { ImGui::GetIO().DisplaySize.x - 220, ImGui::GetIO().DisplaySize.y });
        
        ImGui::SetCursorPos({ 20, 20 });
        ImGui::Text("Browse Apps");
        
        ImGui::SetCursorPos({ 20, 60 });
        ImGui::InputText("Search apps...", m_SearchBuffer, sizeof(m_SearchBuffer));

        ImGui::SetCursorPos({ 20, 100 });
        
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Featured");
        
        for (const auto& app : m_Apps)
        {
            if (app.featured && !app.installed)
            {
                RenderAppCard(app, false);
            }
        }

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "All Apps");
        
        for (const auto& app : m_Apps)
        {
            if (!app.featured)
            {
                RenderAppCard(app, false);
            }
        }

        ImGui::EndChild();
    }

    void RenderInstalledPage()
    {
        ImGui::BeginChild("InstalledContent", { ImGui::GetIO().DisplaySize.x - 220, ImGui::GetIO().DisplaySize.y });
        
        ImGui::SetCursorPos({ 20, 20 });
        ImGui::Text("Installed Apps");
        
        bool hasInstalled = false;
        for (const auto& app : m_Apps)
        {
            if (app.installed)
            {
                hasInstalled = true;
                RenderAppCard(app, true);
            }
        }
        
        if (!hasInstalled)
        {
            ImGui::SetCursorPos({ 20, 100 });
            ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "No apps installed. Browse apps to install some!");
        }

        ImGui::EndChild();
    }

    void RenderSettingsPage()
    {
        ImGui::BeginChild("SettingsContent", { ImGui::GetIO().DisplaySize.x - 220, ImGui::GetIO().DisplaySize.y });
        
        ImGui::SetCursorPos({ 20, 20 });
        ImGui::Text("Settings");
        
        ImGui::SetCursorPos({ 20, 60 });
        ImGui::Text("Account");
        ImGui::SetCursorPos({ 20, 80 });
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), m_UserEmail.c_str());

        ImGui::SetCursorPos({ 20, 120 });
        ImGui::Text("Appearance");
        
        ImGui::SetCursorPos({ 20, 140 });
        ImGui::Checkbox("Dark Mode", &m_DarkMode);

        ImGui::SetCursorPos({ 20, 180 });
        ImGui::Text("About");
        
        ImGui::SetCursorPos({ 20, 200 });
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Shiryu.Launcher v1.0.0");

        ImGui::EndChild();
    }

    void RenderAppCard(const AppInfo& app, bool showLaunch)
    {
        ImGui::BeginChild(("App_" + app.id).c_str(), { 200, 120 }, true);
        
        ImGui::Text(app.name.c_str());
        ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), app.description.c_str());
        
        ImGui::SetCursorPosY(80);
        
        if (app.installed && showLaunch)
        {
            if (ImGui::Button("Launch"))
            {
                // Launch app - will be implemented
            }
        }
        else if (!app.installed)
        {
            if (ImGui::Button("Install"))
            {
                // Install app - will be implemented
            }
        }
        
        ImGui::EndChild();
        
        ImGui::SameLine();
    }

    bool m_IsLoggedIn = false;
    std::string m_UserEmail;
    char m_EmailBuffer[256] = "";
    char m_PasswordBuffer[256] = "";
    char m_SearchBuffer[256] = "";
    bool m_LoginClicked = false;
    bool m_DarkMode = true;
    std::string m_CurrentPage = "home";
    std::vector<AppInfo> m_Apps;
};

Application* CreateApplication(int argc, char** argv)
{
    ApplicationSpecification spec;
    spec.Name = "Shiryu.Launcher";
    spec.CustomTitlebar = true;

    Application* app = new Application(spec);
    std::shared_ptr<LauncherLayer> launcherLayer = std::make_shared<LauncherLayer>();
    app->PushLayer(launcherLayer);
    
    return app;
}

} // namespace ShiryuTeam