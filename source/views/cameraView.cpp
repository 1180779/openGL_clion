
#include "cameraView.hpp"
#include "sceneView.hpp"
#include "../application.hpp"
#include "../objects/camera/camera.hpp"

static sceneView* currentParent;

static void keysCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == currentParent->app.keys.cameraNext && action == GLFW_PRESS) {
        currentParent->scene.cameraMan.nextCamera();
    }
    if(key == currentParent->app.keys.cameraPrev && action == GLFW_PRESS) {
        currentParent->scene.cameraMan.prevCamera();
    }
}

void cameraView::handleInput()
{
    m_parent.scene.cameraMan.getCamera().processInput(
        m_parent.app.window.handle, m_parent.app.keys, m_parent.app.deltaTime());
    if (glfwGetKey(m_parent.app.window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_parent.changeSubView(sceneView::subView::ui);
        return;
    }
}

void cameraView::onEnter()
{
    currentParent = &m_parent;
    glfwSetInputMode(m_parent.app.window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_parent.scene.cameraMan.setCamera();

    glfwSetKeyCallback(m_parent.app.window.handle, keysCallback);
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
    glfwSetCursorPosCallback(m_parent.app.window.handle, nullptr);
    glfwSetScrollCallback(m_parent.app.window.handle, nullptr);
    glfwSetKeyCallback(m_parent.app.window.handle, nullptr);
}
