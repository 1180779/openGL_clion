
#ifndef U1180779_VIEW_H
#define U1180779_VIEW_H

class application;

class view 
{
public:
    view(application& app) : app(app) { }
    virtual void handleInput() = 0;
    virtual void onEnter() = 0;
    virtual void update(float dt) = 0;
    virtual void ui() = 0;
    virtual void render() const = 0;
    virtual void onExit() = 0;
    virtual ~view() { }

    application& app;
};

#endif
