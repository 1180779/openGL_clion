
#ifndef U1180779_CAMERA_MANAGER_H
#define U1180779_CAMERA_MANAGER_H

#include "camera.hpp"
#include <vector>

class cameraManager 
{
public:
    explicit cameraManager(window& window) : m_window(window) { }

    void update(float dt);

    inline void setCamera() { getCamera().setCurrent(m_window); }
    void prevCamera();
    void nextCamera();

    [[nodiscard]] inline const cameraBase& getCamera() const { return *m_cameras[m_curr].get(); }
    inline cameraBase& getCamera() { return *m_cameras[m_curr].get(); }
    [[nodiscard]] inline int getIndex() const { return m_curr; }


    void addCamera(const cameraBase& cam);


private:
    int m_curr = -1; /* current camera index */
    std::vector<std::unique_ptr<cameraBase>> m_cameras;
    window& m_window;
};

#endif