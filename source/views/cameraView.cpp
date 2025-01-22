
#include "cameraView.hpp"
#include "sceneView.hpp"
#include "../application.hpp"
#include "../objects/camera/camera.hpp"

void cameraView::handleInput()
{
    m_parent.scene.cameraMan.getCamera().processInput(
        m_parent.app.window.handle, m_parent.app.deltaTime());
    if (glfwGetKey(m_parent.app.window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_parent.changeSubView(sceneView::subView::ui);
        return;
    }
    if(glfwGetKey(m_parent.app.window.handle, GLFW_KEY_N) == GLFW_PRESS && !m_nDown) 
    {
        m_nDown = true;
        m_parent.scene.cameraMan.nextCamera();
    }
    else if(glfwGetKey(m_parent.app.window.handle, GLFW_KEY_N) == GLFW_RELEASE) 
    {
        m_nDown = false;
    }
}

void cameraView::onEnter()
{
    glfwSetInputMode(m_parent.app.window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_parent.scene.cameraMan.setCamera();
}

void cameraView::update(float dt)
{
    m_parent.scene.update(dt);
}

void cameraView::ui()
{

}

void cameraView::render() const
{

}

void cameraView::onExit()
{
    glfwSetInputMode(m_parent.app.window.handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(m_parent.app.window.handle, NULL);
    glfwSetScrollCallback(m_parent.app.window.handle, NULL);
}
