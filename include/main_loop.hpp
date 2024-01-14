#ifndef MAIN_LOOP_HPP
#define MAIN_LOOP_HPP
#include <common.hpp>
#include <window.hpp>

class MainLoop {
public:
    MainLoop(Window* window) : window(window) { std::cout << "main_loop ctor." << std::endl; }

    void run() {
        // while (!glfwWindowShouldClose(window.getGLFWWindow())) {
        //     // Call virtual functions for update and render
        //     update();
        //     render();

        //     // Swap buffers and poll events
        //     glfwSwapBuffers(window.getGLFWWindow());
        //     glfwPollEvents();
        // }

        double lastFrameTime = 0.0;
        while(!glfwWindowShouldClose(window->getGLFWWindow())){

            double currentTime = glfwGetTime();
            double deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            GLenum error = glGetError();
                if (error != GL_NO_ERROR) {
                std::cerr << "OpenGL Error: " << error << std::endl;
            }
        	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        	glfwSwapBuffers(window->getGLFWWindow());
        	glfwWaitEvents();
        	// glfwPollEvents();
        }
    }

protected:
    virtual void update(){} // = 0; // Pure virtual functions for implementation
    virtual void render(){} //  = 0;

private:
    Window* window;
};

#endif // MAIN_LOOP_HPP