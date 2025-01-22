
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

}
