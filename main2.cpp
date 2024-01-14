#include <common.hpp>
#include <math.hpp>
#include <window.hpp>
#include <shape.hpp>
#include <main_loop.hpp>

int main(){
    Window window = Window::getInstance(1024, 768, "My Application");
    std::cout << "yoyo" << std::endl;
    // std::cout << "Window created with extentions: " << std::endl << window.getGlExtensions() << std::endl;
    // window.getGlMeta();

    // double lastFrameTime = 0.0;
    // while(!glfwWindowShouldClose(window.getGLFWWindow())){

    //     double currentTime = glfwGetTime();
    //     double deltaTime = currentTime - lastFrameTime;
    //     lastFrameTime = currentTime;

    //     GLenum error = glGetError();
    //         if (error != GL_NO_ERROR) {
    //         std::cerr << "OpenGL Error: " << error << std::endl;
    //     }
	// 	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 	glfwSwapBuffers(window.getGLFWWindow());
	// 	glfwWaitEvents();
	// 	// glfwPollEvents();
	// }

    MainLoop ml(&window);
    ml.run();
}