#include <window.hpp>


Window& Window::getInstance(int width, int height, const std::string& title, ErrorCallback errorCallback) {
    static Window instance{width, height, title, errorCallback};
    // std::cout << "instance: " << &(*instance.window) << std::endl;
    return instance;
}

Window::~Window(){
    auto timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S") // Format timestamp
        << " - " << "Object Destroyed" << " - Object ID: " << std::hex << this << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
}

// ... other methods ...
int Window::getWidth() const {
    // glfwSetWindowSize(window, width, getHeight()); 
    return 0;
}
void Window::setWidth(int width) {
    glfwSetWindowSize(window, width, getHeight()); 
}

int Window::getHeight() const {
    // glfwSetWindowSize(window, getWidth(), height);
    return 0;
}
void Window::setHeight(int height) {
    glfwSetWindowSize(window, getWidth(), height);
}

std::string& Window::setTitle() const {
    // glfwSetWindowTitle(window, title.c_str());
    // return glfwGetWindowAttrib;
}
void Window::setTitle(const std::string& title) {
    glfwSetWindowTitle(window, title.c_str());
}
GLFWwindow* Window::getGLFWWindow() const {
    return window;
}

std::string Window::getGlExtensions() const { const GLubyte* extensions = glGetString(GL_EXTENSIONS); return {extensions, extensions + std::strlen((const char*)extensions)}; }

void Window::getGlMeta() const {
    int glVersionMajor, glVersionMinor, glVersionRevision, width, height;
    float x_scale, y_scale;
    int glContextMajorVersion = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int glContextMinorVersion = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    glfwGetVersion(&glVersionMajor, &glVersionMinor, &glVersionRevision);
    glfwGetWindowSize(window, &width, &height);
    glfwGetWindowContentScale(window, &x_scale, &y_scale);

    std::cout << "glfwGetWindowSize width: " << width << std::endl;
    std::cout << "glfwGetWindowSize height: " << height << std::endl;
    std::cout << "glfwGetWindowContentScale x_scale: " << x_scale << std::endl;
    std::cout << "glfwGetWindowContentScale y_scale: " << y_scale << std::endl;
    std::cout << "glVersionMajor: " << glVersionMajor << std::endl;
    std::cout << "glVersionMinor: " << glVersionMinor << std::endl;
    std::cout << "glVersionRevision: " << glVersionRevision << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Rendered: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

Window::Window(int width, int height, const std::string& title, ErrorCallback errorCallback) {
    auto timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S") // Format timestamp
        << " - " << "Object Created" << " - Object ID: " << std::hex << this << std::endl;
    
    // Set custom error callback (if provided)
    if (errorCallback) {
        glfwSetErrorCallback(errorCallback);
    } else {
        glfwSetErrorCallback([](int error, const char* description) {
            std::cerr << "GLFW Error: " << error << " - " << description << std::endl;
        });
    }

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialization failed." << std::endl;
        glfwTerminate();
        throw std::runtime_error("Error: GLFW initialization failed.");
    }

    // Create the window
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        throw std::runtime_error("Error: Failed to create GLFW window.");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL Functions using GLAD.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Error: Failed to initialize OpenGL context" << std::endl;
        throw std::runtime_error("Error: Failed to initialize OpenGL context.");
    }
}