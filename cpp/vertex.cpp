#include<cstdio>
#include<thread>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>


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

int main(){
  glfwInit();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(800,600,"OpenGL",nullptr,nullptr);
  //glfwwindow* window = glfwCreateWindow(800,600,"OpenGL",glfwGetPrimaryMonitor(),nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  printf("%u\n", vertexBuffer);

  float vertices[] = {
    0.0f, 0.5f,
    0.54, -0.5f,
    -0.5f,-0.5f
  };

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
    outColor = vec4(1.0,1.0,1.0,1.0);
  })glsl";

  //GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  //glShaderSource(vertexShader,1,&vertexSource,NULL);
  //glCompileShader(vertexShader);
  //GLint status;
  //glGetShaderiv(vertexShader, GL_COMPILE_STATUS , &status);
  //if (status==GL_TRUE){
  //  printf("compile succesfull");
  //}
  //else{
  //char buffer[512];
  //glGetShaderInfoLog(vertexShader, 512 , NULL,buffer);
  //printf("error message %s\n end", buffer); 
  //};
  GLuint vshader,fshader;
  vshader = compile_shader( vertexSource, GL_VERTEX_SHADER);
  fshader = compile_shader( fragmentSource , GL_FRAGMENT_SHADER);

  //fragment shader
  //GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  //glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  //glCompileShader(fragmentShader);

  while(!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}

