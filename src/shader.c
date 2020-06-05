#include <shader.h>
def(static int , catfile , char * path, char * text, unsigned size)
  FILE *p = fopen(path,"r");
  fread(text,8,size,p);
  text[size] = '\0';
  fclose(p);
  return 0;
end
def(unsigned * , interface_shader , char * vertex_path, char * fragment_path)
  struct stat ft;
  stat(vertex_path, &ft);

  char vertexText[ft.st_size + 1];
  catfile(vertex_path, vertexText, ft.st_size);

  stat(fragment_path,&ft);
  char fragmentText[ft.st_size + 1];
  catfile(fragment_path, fragmentText, ft.st_size);
  
  const char * vertexShaderSource = vertexText;
  const char * fragmentShaderSource = fragmentText;

  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // 检查着色器编译错误
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  cond(!success)
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n",infoLog);
  end
  // 片段着色器
  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // 检查编译错误
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  cond(!success)
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",infoLog);
  end
  // 把着色器链接起来
  unsigned * shaderProgram = (unsigned *)malloc(sizeof(int));
  *shaderProgram = glCreateProgram();
  glAttachShader(*shaderProgram, vertexShader);
  glAttachShader(*shaderProgram, fragmentShader);
  glLinkProgram(*shaderProgram);
  // 检查链接错误
  glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
  cond (!success)
    glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n",infoLog);
  end
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shaderProgram;
end
