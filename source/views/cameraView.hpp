

#ifndef U1180779_CAMERA_VIEW_H
#define U1180779_CAMERA_VIEW_H

#include "subView.hpp"
#include "sceneView.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class sceneView;

class cameraView : public subView<sceneView>
{
public:
    explicit cameraView(sceneView& parent) : subView<sceneView>(parent) { }
    void handleInput() override;
    void onEnter() override;
    void update(float dt) override;
    void ui() override;
    void render() const override;
    void onExit() override;
    ~cameraView() override = default;

private:
    bool m_nDown = false;
};

#endif