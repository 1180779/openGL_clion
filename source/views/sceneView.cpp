
#include "sceneView.hpp"
#include "uiView.hpp"
#include "cameraView.hpp"
#include "../application.hpp"
#include "../../imGui/imgui.h"

sceneView::sceneView(application& app) 
    : view(app), scene(app.window)
{
    scene.addObjects();
    changeSubView(subView::camera);
}

void sceneView::onEnter()
{
    currentSubView->onEnter();
}

void sceneView::handleInput()
{
    currentSubView->handleInput();
}

void sceneView::ui()
{
    currentSubView->ui();

    /* camera pos + framerate window */

    ImGui::SetNextWindowSize(ImVec2(400, 200));
    ImGui::Begin("Camera pos", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::SetNextItemWidth(150);

    if (cameraBase::currentCamera)
    {
        auto& cam = *cameraBase::currentCamera;
        ImGui::Text("index: %d", scene.cameraMan.getIndex());
        ImGui::Text("x = %5.2f", cam.getPos().x);
        ImGui::Text("y = %5.2f", cam.getPos().y);
        ImGui::Text("z = %5.2f", cam.getPos().z);
        ImGui::Text("direction = (%f, %f, %f)", cam.direction.x, cam.direction.y, cam.direction.z);
    }

    const ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    /* help window */

    ImGui::SetNextWindowSize(ImVec2(300, 220));
    ImGui::Begin("Help", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::Text("%15s%3c", "flashlight:", app.keys.flashlight);

    ImGui::Spacing();
    ImGui::Text("Camera key binds:");

    ImGui::Spacing();
    ImGui::Text("%15s%3c", "next camera:", app.keys.cameraNext);
    ImGui::Text("%15s%3c", "prev camera:", app.keys.cameraPrev);

    ImGui::Spacing();
    ImGui::Text("%15s%3c", "forward:", app.keys.forward);
    ImGui::Text("%15s%3c", "backward:", app.keys.backward);
    ImGui::Text("%15s%3c", "left:", app.keys.left);
    ImGui::Text("%15s%3c", "right:", app.keys.right);
    ImGui::Text("%15s%3c", "up:", app.keys.up);
    ImGui::Text("%15s%3c", "down:", app.keys.down);

    ImGui::End();
}

void sceneView::update(float dt)
{
    /* TODO: add animations */
    currentSubView->update(dt);
}

void sceneView::render() const
{
    if (scene.lightMan.fog) {
        const auto& col = scene.lightMan.fogColor;
        glClearColor(col.x, col.y, col.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    scene.render();
}

void sceneView::onExit()
{
    if(currentSubView) currentSubView->onExit();
    /* add back ui callbacks */
    glfwSetCursorPosCallback(app.window.handle,  ImGui_ImplGlfw_CursorPosCallback);
    glfwSetScrollCallback(app.window.handle, ImGui_ImplGlfw_ScrollCallback);
}

void sceneView::changeSubView(subView newSubView)
{
    switch(newSubView) 
    {
    case subView::ui:
        if (currentSubView) currentSubView->onExit();
        if (!m_subViews.ui) m_subViews.ui = std::make_shared<uiView>(*this);
        currentSubView = m_subViews.ui;
        currentSubView->onEnter();
        break;
    case subView::camera:
        if (currentSubView) currentSubView->onExit();
        if (!m_subViews.camera) m_subViews.camera = std::make_shared<cameraView>(*this);
        currentSubView = m_subViews.camera;
        currentSubView->onEnter();
        break;
    }
}
