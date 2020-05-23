#include <head.h>
#include <stdio.h>
#include <string.h>
#ifndef _MESH_
#define _MESH_
typedef char string[1024];
typedef float vec2[2];
typedef float vec3[3];

interface(Vertex){
  vec3 Position;
  vec3 Normal;
  vec2 TexCoords;
  vec3 Tangent;
  vec3 Bitangent;
};

interface(Vertex_array){
  Vertex * vertices;
  unsigned vertices_Size;
};


interface(Index_array){
  unsigned * indices;
  unsigned indices_Size;
};

interface(Texture){
  unsigned id;
  string type;
  string path;
};

interface(Texture_array){
  Texture * textures;
  unsigned textures_Size;
};

interface(Mesh){
  unsigned * shader;
  Vertex_array * vertex_array;
  Index_array * index_array;
  Texture_array * texture_array;
  unsigned VAO,EBO,VBO;
  void(*render)(Mesh*);
};
Mesh * interface_Mesh(unsigned * shader, Vertex_array * va, Index_array * ia,Texture_array * ta);
#endif
