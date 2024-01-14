// glfw + opengl prog i wrote in office.

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cstddef>
#include <random>
#include <chrono>
#include <cmath>

// #include <OpenGL/gl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include <libavcodec/avcodec.h>
// #include <libavformat/avformat.h>
// #include <libswscale/swscale.h>
// #include <inttypes.h>

// #include <ft2build.h>
// #include FT_FREETYPE_H

#define debug_shape true
#define debug_meta_info false
#define debug_window_changed false
#define debug_mouse_key false
#define debug_mouse_cursor false
#define debug_mouse_scroll false
#define debug_key false

double inline getPi(){
	return 2 * std::acos(0.0); // or alternatively use 2 * std::asin(1.0f) or directly return 3.141593;
}

double inline getTau(){
	return 4 * std::acos(0.0); // or alternatively use 4 * std::asin(1.0f) or directly return 2 * 3.141593;
}

void fix_render_on_mac(GLFWwindow* window) {
#ifdef __APPLE__
    static bool macMoved = false;
    if(!macMoved) {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
        macMoved = true;
    }
#endif
}

int rng_int(int min, int max) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

float rng_real(float min, float max) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

class Shape {
public:
    // Constructors
    Shape() = default;
    Shape(float pos_x, float pos_y, float size, float col_r = 1.0f, float col_g = 1.0f, float col_b = 1.0f)
        : position({pos_x, pos_y}), color({col_r, col_g, col_b}), size(size) {
		// createVAO();
		if (debug_shape){
			std::cout << "x_pos: " << position.x << ", y_pos: " << position.y << std::endl;
			std::cout << "r_col: " << color.r << ", g_col: " << color.g << ", b_col: " << color.b << std::endl;
			std::cout << "size: " << size << std::endl;
		}
	}

    // Getters and setters
    glm::vec2 getPosition() const { return position; }
    void setPosition(float pos_x, float pos_y) { position = {pos_x, pos_y}; }

    glm::vec3 getColor() const { return color; }
    void setColor(float col_r, float col_g, float col_b) { color = {col_r, col_g, col_b}; }

    float getSize() const { return size; }
    void setSize(float size) { size = size; }

	float getAngle() const { return angle;}
	void setAngle(float angle) { angle = angle; }

	glm::vec2 getDelta() const { return delta; }
	void setDelta(float delta_x, float delta_y) { delta = {delta_x, delta_y}; }

	// void createVAO() {
	// 	// Generate and bind VAO
	// 	std::cout << "bind VAO started." << std::endl;
	// 	glGenVertexArrays(1, &vao);
	// 	std::cout << "bind VAO mid." << std::endl;
	// 	glBindVertexArray(vao);
	// 	std::cout << "bind VAO success." << std::endl;

	// 	// Create and bind VBO for vertex data
	// 	unsigned int vbo;
	// 	glGenBuffers(1, &vbo);
	// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// 	std::cout << "bind VBO success." << std::endl;

	// 	// Vertex data for the square
	// 	GLfloat vertices[] = {
	// 		-size / 2, -size / 2, 0.0f,
	// 		+size / 2, -size / 2, 0.0f,
	// 		+size / 2, +size / 2, 0.0f,
	// 		-size / 2, +size / 2, 0.0f
	// 	};
	// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 	// Specify vertex attribute layout
	// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	// 	glEnableVertexAttribArray(0);
	// }

	// void draw() const {
	// 	glBindVertexArray(vao); // Assuming a VAO is created and bound
	// 	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	// }


    // Draw the square
    void draw() const {
		// glEnableClientState(GL_VERTEX_ARRAY);
        // glVertexPointer(3, GL_FLOAT, 0, vertices);

		GLfloat positionArray[] = { position.x, position.y, 0.0f };

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, positionArray);

		// glEnableClientState(GL_COLOR_ARRAY);
		// glColorPointer(3, GL_FLOAT, 0, colorArray);
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_QUADS);
        glVertex3f(position.x - size / 2.0f, position.y - size / 2, 0.0f);
        glVertex3f(position.x + size / 2.0f, position.y - size / 2, 0.0f);
        glVertex3f(position.x + size / 2.0f, position.y + size / 2, 0.0f);
        glVertex3f(position.x - size / 2.0f, position.y + size / 2, 0.0f);
        glEnd();

		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2i(position.x, position.y);
		glVertex2i(position.x + delta.x * 5, position.y + delta.y * 5);
		glEnd();

		if (debug_shape){
			std::cout << "x_pos: " << position.x << ", y_pos: " << position.y << std::endl;
			std::cout << "r_col: " << color.r << ", g_col: " << color.g << ", b_col: " << color.b << std::endl;
			std::cout << "size: " << size << std::endl;
		}

		// GLfloat positionArray[] = { position.x, position.y, 0.0f }; // Adjust for 3D rendering
		// GLfloat colorArray[] = { color.r, color.g, color.b };

		// glEnableClientState(GL_VERTEX_ARRAY);
		// glVertexPointer(3, GL_FLOAT, 0, positionArray); // Use 3 components for vertices

		// glEnableClientState(GL_COLOR_ARRAY);
		// glColorPointer(3, GL_FLOAT, 0, colorArray);

		// glBegin(GL_QUADS);
		// glVertex3fv(positionArray); // Use positionArray for vertices
		// glVertex3f(position.x + size, position.y, 0.0f);
		// glVertex3f(position.x + size, position.y + size, 0.0f);
		// glVertex3f(position.x, position.y + size, 0.0f);
		// glEnd();
    }

	void update(GLFWwindow* window){
		float speed = 0.1f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if(debug_key) std::cout << "W key pressed: Move up." << std::endl;
			position.y += 5.0f;
			position += delta;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if(debug_key) std::cout << "A key pressed: Move left." << std::endl;
			position.x -= 5.0f;
			angle -= 0.1;
			if(angle < 0){angle += getTau(); }
			delta = {std::cos(angle) * 5, std::sin(angle) * 5};
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if(debug_key) std::cout << "S key pressed: Move down." << std::endl;
			position.y -= 5.0f;
			position -= delta;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if(debug_key) std::cout << "D key pressed: Move right." << std::endl;
			position.x += 5.0f;
			angle += 0.1;
			if(angle > getTau()){angle += getTau(); }
			delta = {std::cos(angle) * 5, std::sin(angle) * 5};
		}
	}

private:
    glm::vec2 position; // Position of the square's center
    glm::vec3 color;    // Color of the square
    float size;         // Size of the square (side length)
	glm::vec2 delta;    // delta_x and delta_y for angle/rotation
	double angle;
	// unsigned int vao;
};
typedef std::vector<Shape> Shapes;

void initShapes(Shapes& shapes, std::size_t size, GLFWwindow* window){
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	std::cout << "width: " << width << ", height: " << height << std::endl;

	for(int i = 0; i < size; i++){
		shapes.push_back({
			(float)rng_int(0, width), // get random x_pos.
			(float)rng_int(0, height), // get random y_pos.
			(float)rng_int(10, 50),  // get random size.
			rng_real(0.0f, 1.0f), // get random r_col.
			rng_real(0.0f, 1.0f), // get random g_col.
			rng_real(0.0f, 1.0f) // get random b_col.
			
		});
	}
}

void error_callback(int error, const char* description){
    std::cerr << "Error:" << description << std::endl;
}

// void GLAPIENTRY glDebugMessageHandle(GLenum source, GLenum type, GLuint id, GLenum soverity, GLsizei length, const GLchar* message, const void* userParam){
// 	std::cout << "OpenGL Error: " << message << std::endl;
// }

void glDebugMessageHandle(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
    (void) source;
    (void) id;
    (void) length;
    (void) userParam;
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void glSetFrameBufferSizeHandle(GLFWwindow* window, int width, int height) {
	if(debug_window_changed){ std::cout << "window size changed to width: " << width << ", height: " << height << std::endl;}
	glViewport(0, 0, width, height);
}

void glSetKeyHandle(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	// std::cout << "Key pressed: " << key << std::endl;
	// Alternatively, you can print the key as a character.
    // char keyChar = static_cast<char>(key);
    // const char* key_name = glfwGetKeyName(key, 0);
    // std::cout << "Key pressed: " << key_name << " (" << key << ") ." << std::endl;

	if(action == GLFW_PRESS){
		switch(key){
			case GLFW_KEY_ESCAPE:
				// close window
				if(debug_key) std::cout << "ESC button pressed." << std::endl;
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_W:
				// Move texture up
				if(debug_key) std::cout << "W key pressed: Move up." << std::endl;
				break;
			case GLFW_KEY_A:
				// Move texture left
				if(debug_key) std::cout << "A key pressed: Move left." << std::endl;
				break;
			case GLFW_KEY_S:
				// Move texture down
				if(debug_key) std::cout << "S key pressed: Move down." << std::endl;
				break;
			case GLFW_KEY_D:
				// Move texture right
				if(debug_key) std::cout << "D key pressed: Move right." << std::endl;
				break;
		}
	}

	if(debug_key){
		char keyChar = static_cast<char>(key);
		if (action == GLFW_PRESS) {
			std::cout << "Key pressed: " << keyChar << " (" << key << ") ." << std::endl;
		} else if (action == GLFW_RELEASE) {
			std::cout << "Key released: " << keyChar << " (" << key << ") ." << std::endl;
		} else if (action == GLFW_REPEAT) {
			std::cout << "Key repeat: " << keyChar << " (" << key << ") ." << std::endl;
		}
	}
}

void glSetMouseButtonHandle(GLFWwindow* window, int button, int action, int mods){
	if(debug_mouse_key){
		if(action == GLFW_PRESS){
			if(button == GLFW_MOUSE_BUTTON_LEFT){
				std::cout << "Left mouse button pressed." << std::endl;
			}else if(button == GLFW_MOUSE_BUTTON_RIGHT){
				std::cout << "Right mouse button pressed." << std::endl;
			}else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
				std::cout << "Middle mouse button pressed." << std::endl;
			}
		}else if(action == GLFW_RELEASE){
			if(button == GLFW_MOUSE_BUTTON_LEFT){
				std::cout << "Left mouse button released." << std::endl;
			}else if(button == GLFW_MOUSE_BUTTON_RIGHT){
				std::cout << "Right mouse button released." << std::endl;
			}else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
				std::cout << "Middle mouse button released." << std::endl;
			}
		}
	}
}

void glSetCursorPosHandle(GLFWwindow* window, double xpos, double ypos) {
    if(debug_mouse_cursor){std::cout << "Mouse Cursor position: (" << xpos << ", " << ypos << ")." << std::endl;}
}

void glSetScrollHandle(GLFWwindow* window, double xoffset, double yoffset) {
    if(debug_mouse_scroll){std::cout << "Mouse Scroll offset: (" << xoffset << ", " << yoffset << ")." << std::endl;}
}

int main(int argc, const char** argv) {

	if (!glfwInit()) {
		std::cerr << "Error: GLFW initialization failed." << std::endl;
		return 1;
	}

	glfwSetErrorCallback(error_callback);

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Set GLFW hints for a borderless window
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Get the primary monitor
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

	if (!primaryMonitor) {
		std::cerr << "Error: Failed to get the primary monitor." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Get the video mode of the primary monitor
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	if (!mode) {
		std::cerr << "Error: Failed to get video mode." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Print the width and height of the primary monitor
	// int primaryMonitorWidth = mode->width;
	// int primaryMonitorHeight = mode->height;
	int primaryMonitorWidth = 1024;
	int primaryMonitorHeight = 720;
	std::cout << "Primary Monitor Width: " << primaryMonitorWidth << std::endl;
	std::cout << "Primary Monitor Height: " << primaryMonitorHeight << std::endl;
	
	// creating window with height, width and title.
	std::string window_title {"GLFW Window."};
	GLFWwindow* window = glfwCreateWindow(primaryMonitorWidth, primaryMonitorHeight, window_title.c_str(), NULL, NULL);
	// GLFWwindow* window = glfwCreateWindow(1024, 720, window_title.c_str(), NULL, NULL);

	if(!window){
		std::cerr << "Error: Failed to create window." << std::endl;
		glfwTerminate();
		return 1;
	}

    // glfwSetErrorCallback(error_callback);
    // Set handle to process Window Size Changed (Resize Window) Events on a window.
    glfwSetFramebufferSizeCallback(window, glSetFrameBufferSizeHandle);
    // Set handle to process Keyboard Events on a window.
	glfwSetKeyCallback(window, glSetKeyHandle);
    // Set handle to process Mouse Button Events on a window.
	glfwSetMouseButtonCallback(window, glSetMouseButtonHandle);
    // Set handle to process Mouse Scroll Events on a window.
	glfwSetScrollCallback(window, glSetScrollHandle);
    // Set handle to process Mouse Cursor Position Change events on a window.
	glfwSetCursorPosCallback(window, glSetCursorPosHandle);

	unsigned char* data = new unsigned char[100 * 100 * 3];
	for(auto i = 0; i < 100; i++){
		for(auto j = 0; j < 100; j++){
			data[i * 100 * 3 + j * 3    ] = 0xff;
			data[i * 100 * 3 + j * 3 + 1] = 0x00;
			data[i * 100 * 3 + j * 3 + 2] = 0x00;
		}
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Error: Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

	// glEnable(GL_DEBUG_OUTPUT);
	// glDebugMessageCallback(glDebugMessageHandle, 0);
	if(debug_meta_info){
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

	if (glDebugMessageCallback != NULL) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(glDebugMessageHandle, 0);
    }

	// if (glDrawArraysInstanced == NULL) {
    //     fprintf(stderr, "Support for EXT_draw_instanced is required!\n");
    //     exit(1);
    // }

	// following lines copy pasted and slapped from : https://stackoverflow.com/questions/43985162/opengl-or-glfw-renders-ok-only-when-moving-the-window
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0.0f, 0.0f, primaryMonitorWidth, primaryMonitorHeight);
    glOrtho(0, primaryMonitorWidth, 0, primaryMonitorHeight, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// Shape square(500, 500, 50, 0.5f, 0.8f, 0.2f); // Green square at (100, 100) with size 50
	Shapes shapes;
	initShapes(shapes, 1, window);

	while(!glfwWindowShouldClose(window)){
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGetError();
		for(auto& shape: shapes){
			shape.update(window);
			shape.draw();
		}
		glGetError();
		glfwSwapBuffers(window);
		fix_render_on_mac(window);
		glfwWaitEvents();
		// glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
	return 0;
}
