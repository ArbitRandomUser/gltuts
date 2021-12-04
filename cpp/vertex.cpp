#include<stdio.h>
#include <unistd.h>
#include<thread>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>



GLuint compile_shader(const char* , GLuint );

int main(){
  printf("GLERROR %d\n",glGetError());
  //
  glfwInit();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  GLFWwindow* window = glfwCreateWindow(640,480,"OpenGL",nullptr,nullptr);
  //glfwwindow* window = glfwCreateWindow(800,600,"OpenGL",glfwGetPrimaryMonitor(),nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vao;
  glGenVertexArrays(1, &vao);

  GLuint vao2;
  glGenVertexArrays(1,&vao2);

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  printf("%u\n", vertexBuffer);
  printf("GLERROR %d\n",glGetError());

  GLfloat vertices[] = {
  /*0*/  0.0f, 0.5f,
  /*1*/  0.5f, -0.5f,
  /*2*/  -0.5f,-0.5f,
  /*3*/  0.0f, -0.6f,
  /*4*/  0.0f, 0.5f,
  };

  printf("GLERROR %d\n",glGetError());
  GLuint vbo; 
  glGenBuffers(1,&vbo); //generate a buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbo);//bind buffer type to vbo 
  glBufferData(GL_ARRAY_BUFFER , sizeof(vertices),vertices,GL_STATIC_DRAW);

  //vertex shader
  const char* vertexSource = R"glsl( #version 150 core
  in vec2 position;
  void main(){
    gl_Position = vec4(position,0.0,1.0);
  })glsl";
  //fragment shader
  const char* fragmentSource = R"glsl( 
  #version 150 core
  out vec4 outColor;
  void main(){
    outColor = vec4(1.0,1.0,1.0,0.3);
  })glsl";

  GLuint vshader,fshader;
  vshader = compile_shader( vertexSource, GL_VERTEX_SHADER);
  fshader = compile_shader( fragmentSource , GL_FRAGMENT_SHADER);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,vshader);
  glAttachShader(shaderProgram,fshader);
  //glBindFragDataLocation(shaderProgram, 0, "outColor");
  glBindVertexArray(vao);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);
  GLint posAttrib = glGetAttribLocation(shaderProgram,"position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib , 2 , GL_FLOAT, GL_FALSE, 2*sizeof(float) , 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES,0,3);
  //glDrawArrays(GL_TRIANGLES,1,3);
  //glDrawArrays(GL_LINES,0,2);
  //glDrawArrays(GL_LINES,1,2);
  //glDrawArrays(GL_LINES,2,2);
  //glDrawArrays(GL_LINES,3,2);
  //glDrawArrays(GL_TRIANGLES,0,3);


  printf("GLERROR after triangle%d\n",glGetError());
  while(!glfwWindowShouldClose(window))
  {
    //glDrawArrays(GL_TRIANGLES,2,3);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);   //glDrawArrays(GL_TRIANGLES,0,3);
    glDrawArrays(GL_TRIANGLES,0,3);
    glfwPollEvents();
    glfwSwapBuffers(window);
    //sleep(1);
  }
  glfwTerminate();
}

GLuint compile_shader(const char* shadersource, GLuint shadertype){
  //compilers a shader
  GLuint shader = glCreateShader(shadertype);
  glShaderSource(shader,1,&shadersource,NULL);
  glCompileShader(shader);
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS , &status);
  if (status == GL_TRUE){
    printf("%d compile succesful\n", shader);}
  else{
    char buffer[512];
    glGetShaderInfoLog(shader,512,NULL,buffer);
    printf("SHADER COMPILE ERROR %s\n",buffer);}
  return shader;
}
