#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <common.hpp>

class Window {
public:
    using ErrorCallback = void (*)(int error, const char* description);

    static Window& getInstance(int width = 800, int height = 600, const std::string& title = "Window", ErrorCallback errorCallback = nullptr);

    ~Window();

    int getWidth() const;
    void setWidth(int width);

    int getHeight() const;
    void setHeight(int height);

    std::string& setTitle() const;
    void setTitle(const std::string& title);

    GLFWwindow* getGLFWWindow() const;
    std::string getGlExtensions() const;
    void getGlMeta() const;

private:
    // Private constructor to prevent direct instantiation
    Window(int width = 800, int height = 600, const std::string& title = "Window", ErrorCallback errorCallback = nullptr);

    GLFWwindow* window;
};

#endif // WINDOW_HPP