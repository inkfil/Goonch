#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <common.hpp>
#include <math.hpp>

class Shape {
public:
    // Constructors
    Shape() = default;
    Shape(float pos_x, float pos_y, float size, float col_r = 1.0f, float col_g = 1.0f, float col_b = 1.0f);

    // Getters and setters
    glm::vec2 getPosition() const;
    void setPosition(float pos_x, float pos_y);

    glm::vec3 getColor() const;
    void setColor(float col_r, float col_g, float col_b);

    float getSize() const;
    void setSize(float size);

    float getAngle() const;
    void setAngle(float angle);

    glm::vec2 getDelta() const;
    void setDelta(float delta_x, float delta_y);
    virtual void draw() const = 0;
    virtual void update(GLFWwindow* window, double deltaTime) = 0;

private:
    glm::vec3 position; // Position of the square's center
    glm::vec3 color;    // Color of the square
    float size;         // Size of the square (side length)
	glm::vec3 delta;    // delta_x and delta_y for angle/rotation
	double angle;
};

typedef std::vector<Shape> Shapes;

#endif // SHAPE_HPP