
#include <shape.hpp>

Shape::Shape(float pos_x, float pos_y, float size, float col_r, float col_g, float col_b)
    : position({pos_x, pos_y, 0.0f}), color({col_r, col_g, col_b}), size(size) {
    // createVAO();
}

glm::vec2 Shape::getPosition() const { return position; }
void Shape::setPosition(float pos_x, float pos_y) { position = {pos_x, pos_y, 0.0f}; }

glm::vec3 Shape::getColor() const { return color; }
void Shape::setColor(float col_r, float col_g, float col_b) { color = {col_r, col_g, col_b}; }

float Shape::getSize() const { return size; }
void Shape::setSize(float size) { size = size; }

float Shape::getAngle() const { return angle;}
void Shape::setAngle(float angle) { angle = angle; }

glm::vec2 Shape::getDelta() const { return delta; }
void Shape::setDelta(float delta_x, float delta_y) { delta = {delta_x, delta_y, 0.0f}; }

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
void Shape::draw() const {
    // glEnableClientState(GL_VERTEX_ARRAY);
    // glVertexPointer(3, GL_FLOAT, 0, vertices);

    GLfloat positionArray[] = { position.x, position.y, position.z };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, positionArray);

    // glEnableClientState(GL_COLOR_ARRAY);
    // glColorPointer(3, GL_FLOAT, 0, colorArray);
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_QUADS);
    glVertex3f(position.x - size / 2.0f, position.y - size / 2, position.z);
    glVertex3f(position.x + size / 2.0f, position.y - size / 2, position.z);
    glVertex3f(position.x + size / 2.0f, position.y + size / 2, position.z);
    glVertex3f(position.x - size / 2.0f, position.y + size / 2, position.z);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(position.x, position.y);
    glVertex2i(position.x + delta.x * 5, position.y + delta.y * 5);
    glEnd();

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

void Shape::update(GLFWwindow* window, double deltaTime){
    float speed = 0.1f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W key pressed: Move up." << std::endl;
        position.y += 5.0f;
        position += delta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A key pressed: Move left." << std::endl;
        position.x -= 5.0f;
        angle -= 0.1;
        if(angle < 0){angle += getTau(); }
        delta = {std::cos(angle) * 5, std::sin(angle) * 5, 0.0f};
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "S key pressed: Move down." << std::endl;
        position.y -= 5.0f;
        position -= delta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        std::cout << "D key pressed: Move right." << std::endl;
        position.x += 5.0f;
        angle += 0.1;
        if(angle > getTau()){angle += getTau(); }
        delta = {std::cos(angle) * 5, std::sin(angle) * 5, 0.0f};
    }
}


