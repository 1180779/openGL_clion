
#ifndef U1180779_SCENE_VIEW_H
#define U1180779_SCENE_VIEW_H

#include "view.hpp"
#include "../objects/sceneManager.hpp"

#include "subView.hpp"

class cameraView;
class uiView;

class application;

class sceneView : public view
{
public:
    sceneView(application& app);
    void onEnter() override;
    void handleInput() override;
    void ui() override;
    void update(float dt) override;
    void render() const override;
    void onExit() override;
    ~sceneView() override;

    enum class subView
    {
        ui,
        camera
    };

    void changeSubView(subView newSubView);

    sceneManager scene;
    struct subViews 
    {
        std::shared_ptr<uiView> ui;
        std::shared_ptr<cameraView> camera;
    } m_subViews;
    std::shared_ptr<::subView<sceneView> > currentSubView;
};

#endif