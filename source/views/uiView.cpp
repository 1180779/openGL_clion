
#include "uiView.hpp"
#include "sceneView.hpp"
#include "../application.hpp"

#include "../../imGui/imgui.h"

#include "../../imGui/imgui_impl_glfw.h"

void uiView::handleInput()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) 
    {
        m_parent.changeSubView(sceneView::subView::camera);
        return;
    }
}

void uiView::onEnter()
{
    glfwSetInputMode(m_parent.app.window.handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(m_parent.app.window.handle, ImGui_ImplGlfw_CursorPosCallback);
    glfwSetScrollCallback(m_parent.app.window.handle, ImGui_ImplGlfw_ScrollCallback);
}

void uiView::ui()
{
    ImGui::SetNextWindowSize(ImVec2(300, 120));
    ImGui::Begin("Settings", nullptr,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Checkbox("day",
        &m_parent.scene.lightMan.day);
    ImGui::Checkbox("ortho (per camera)",
        &m_parent.scene.cameraMan.getCamera().ortho);
    ImGui::Checkbox("fog",
        &m_parent.scene.lightMan.fog);
    ImGui::SliderFloat("fog density", &m_parent.scene.lightMan.fogDensity, 0.0f, 0.4f);
    ImGui::End();
}
