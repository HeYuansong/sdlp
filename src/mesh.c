#include <mesh.h>
def(static void, render,Mesh*mesh)
  unsigned int diffuseNr  = 0;
  unsigned int specularNr = 0;
  unsigned int normalNr   = 0;
  unsigned int heightNr   = 0;
  times(mesh->texture_array->textures_Size)
    glActiveTexture(GL_TEXTURE0 + i);
    string number;
    printf("path:%s\n",mesh->texture_array->textures[i].path);
    if(strcmp(mesh->texture_array->textures[i].type,"texture_diffuse") == 0)
      sprintf(number,"material.texture_diffuse%d",diffuseNr++);
    else if(strcmp(mesh->texture_array->textures[i].type,"texture_specular") == 0)
      sprintf(number,"material.texture_specular%d",specularNr++);
    else if(strcmp(mesh->texture_array->textures[i].type,"texture_normal") == 0)
      sprintf(number,"material.texture_normal%d",normalNr++);
    else if(strcmp(mesh->texture_array->textures[i].type,"texture_height") == 0)
      sprintf(number,"material.texture_height%d",heightNr++);
    printf("number:%s\n",number);
    glUniform1i(glGetUniformLocation(*mesh->shader, number), i);
    glBindTexture(GL_TEXTURE_2D, mesh->texture_array->textures[i].id);
  end
  glUseProgram(*mesh->shader);
  glBindVertexArray(mesh->VAO);
  glDrawElements(GL_TRIANGLES, mesh->index_array->indices_Size, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glActiveTexture(GL_TEXTURE0);
end
def(Mesh * , interface_Mesh, unsigned * shader, Vertex_array * va, Index_array * ia,Texture_array * ta)
  Mesh * mesh =  (Mesh*)malloc(sizeof(Mesh));
  mesh->shader = shader;
  mesh->render = render;
  mesh->vertex_array = va;
  mesh->index_array = ia;
  mesh->texture_array = ta;
  glGenVertexArrays(1, &mesh->VAO);
  glGenBuffers(1, &mesh->VBO);
  glGenBuffers(1, &mesh->EBO);
  glBindVertexArray(mesh->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  glBufferData(GL_ARRAY_BUFFER, va->vertices_Size * sizeof(Vertex), &va->vertices[0], GL_STATIC_DRAW);  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ia->indices_Size * sizeof(unsigned), &ia->indices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);	
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
  glEnableVertexAttribArray(2);	
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
  glBindVertexArray(0);
  return mesh;
end
