#include "ShiryuTeam/Application.h"
#include "ShiryuTeam/EntryPoint.h"

#include "ShiryuTeam/Image.h"
#include "ShiryuTeam/UI/UI.h"

class ExampleLayer : public ShiryuTeam::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();

		UI_DrawAboutModal();
	}

	void UI_DrawAboutModal()
	{
		if (!m_AboutModalOpen)
			return;

		ImGui::OpenPopup("About");
		m_AboutModalOpen = ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (m_AboutModalOpen)
		{
			auto image = ShiryuTeam::Application::Get().GetApplicationIcon();
			ImGui::Image(image->GetDescriptorSet(), { 48, 48 });

			ImGui::SameLine();
			ShiryuTeam::UI::ShiftCursorX(20.0f);

		ImGui::BeginGroup();
		ImGui::Text("ShiryuTeam application framework");
		ImGui::Text("by Studio Shiryu.");
		ImGui::EndGroup();

			if (ShiryuTeam::UI::ButtonCentered("Close"))
			{
				m_AboutModalOpen = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	void ShowAboutModal()
	{
		m_AboutModalOpen = true;
	}
private:
	bool m_AboutModalOpen = false;
};

ShiryuTeam::Application* ShiryuTeam::CreateApplication(int argc, char** argv)
{
	ShiryuTeam::ApplicationSpecification spec;
	spec.Name = "Shiryu Team Dashboard";
	spec.CustomTitlebar = true;

	ShiryuTeam::Application* app = new ShiryuTeam::Application(spec);
	std::shared_ptr<ExampleLayer> exampleLayer = std::make_shared<ExampleLayer>();
	app->PushLayer(exampleLayer);
	app->SetMenubarCallback([app, exampleLayer]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				exampleLayer->ShowAboutModal();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}