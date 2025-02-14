
#ifndef U1180779_APPLICATION_H
#define U1180779_APPLICATION_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../imGui/imgui_impl_glfw.h"

#include "window.hpp"
#include "deltaTime.hpp"
#include "keyBinds.hpp"

#include "views/sceneView.hpp"

class view;
class sceneView;

class application 
{
public:

    /* structures */

    enum view 
    {
        scene,
        menu
    };

    struct views 
    {
        std::shared_ptr<sceneView> scene;
    };

    /* avaliable methods */

    application();
    void run();
    void changeView(view newView);
    ~application();

    /* public variables */

    deltaTime deltaTime;
    window window;
    keyBinds keys;

private:

    /* private variables */
    std::shared_ptr<::view> m_currentView;
    views m_views;
    view m_activeView = view::scene;
};

#endif