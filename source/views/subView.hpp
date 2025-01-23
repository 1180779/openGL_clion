
#ifndef U1180779_SUB_VIEW_H
#define U1180779_SUB_VIEW_H

template <typename ParentViewT>
class subView
{
public:
    explicit subView(ParentViewT& parent) : m_parent(parent) { }
    virtual void handleInput() = 0;
    virtual void onEnter() = 0;
    virtual void update(float dt) = 0;
    virtual void ui() = 0;
    virtual void render() const = 0;
    virtual void onExit() = 0;
    virtual ~subView() = default;

protected:
    ParentViewT& m_parent;
};

#endif