

#ifndef U1180779_UI_VIEW_H
#define U1180779_UI_VIEW_H

#include "subView.hpp"
#include "sceneView.hpp"

class uiView : public subView<sceneView>
{
public:
    uiView(sceneView& parent) : subView(parent) { }
    void handleInput() override;
    void onEnter() override;
    void update(float dt) override { }
    void ui() override;
    void render() const override { }
    void onExit() override { }
    ~uiView() override { }
};

#endif