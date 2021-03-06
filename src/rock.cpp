#include "rock.h"
#include "main.h"

Rock::Rock(float x, float z) {
    this->position = glm::vec3(x, -1, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float a=0,b=0,c=0;
    static const GLfloat vertex_buffer_data[] = {
        -a,-b,-c, // triangle 1 : begin
        -a,-b, c,
        -a, b, c, // triangle 1 : end

        a, b,-c, // triangle 2 : begin
        -a,-b,-c,
        -a, b,-c, // triangle 2 : end

        a,-b, c,
        -a,-b,-c,
        a,-b,-c,

        a, b,-c,
        a,-b,-c,
        -a,-b,-c,

        -a,-b,-c,
        -a, b, c,
        -a, b,-c,

        a,-b, c,
        -a,-b, c,
        -a,-b,-c,

        -a, b, c,
        -a,-b, c,
        a,-b, c,

        a, b, c,
        a,-b,-c,
        a, b,-c,

        a,-b,-c,
        a, b, c,
        a,-b, c,

        a, b, c,
        a, b,-c,
        -a, b,-c,

        a, b, c,
        -a, b,-c,
        -a, b, c,

        a, b, c,
        -a, b, c,
        a,-b, c
    };
    float len = 0.5;
    static const GLfloat vertex_buffer_data1[] = {
      -0.25,-0.25,-0.25, // triangle 1 : begin
        -0.25,-0.25, 0.25,
        -0.125, 0.25, 0.125, // triangle 1 : end

        0.125, 0.25,-0.125, // triangle 2 : begin
        -0.25,-0.25,-0.25,
        -0.125, 0.25,-0.125, // triangle 2 : end

        0.25,-0.25, 0.25,
        -0.25,-0.25,-0.25,
        0.25,-0.25,-0.25,

        0.125, 0.25,-0.125,
        0.25,-0.25,-0.25,
        -0.25,-0.25,-0.25,

        -0.25,-0.25,-0.25,
        -0.125, 0.25, 0.125,
        -0.125, 0.25,-0.125,

        0.25,-0.25, 0.25,
        -0.25,-0.25, 0.25,
        -0.25,-0.25,-0.25,

        -0.125, 0.25, 0.125,
        -0.25,-0.25, 0.25,
        0.25,-0.25, 0.25,

        0.125, 0.25, 0.125,
        0.25,-0.25,-0.25,
        0.125, 0.25,-0.125,

        0.25,-0.25,-0.25,
        0.125, 0.25, 0.125,
        0.25,-0.25, 0.25,

        0.125, 0.25, 0.125,
        0.125, 0.25,-0.125,
        -0.125, 0.25,-0.125,

        0.125, 0.25, 0.125,
        -0.125, 0.25,-0.125,
        -0.125, 0.25, 0.125,

        0.125, 0.25, 0.125,
        -0.125, 0.25, 0.125,
        0.25,-0.25, 0.25
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rock::tick(int is_wind, int dir) {
  if(is_wind)
  {
    if(dir)
    this->position.x -= 0.002;
    else
    this->position.x += 0.004;

    this->position.z -= 0.002;
  }
}

bounding_box_t Rock::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z};
  return bbox;
}
