#include <box.h>

def(static void ,setVec3,vec3 vector,float x,float y,float z)
  vector[0] = x;
  vector[1] = y;
  vector[2] = z;
end

def(Mesh *, interface_Box ,unsigned * shader, float x, float y, float w, float h)
  Vertex_array * va = (Vertex_array*)malloc(sizeof(Vertex_array));
  Vertex * vertices = (Vertex*)malloc(sizeof(Vertex)*4);
  setVec3(vertices[0].Position,x+w/2,y+h/2,0);
  setVec3(vertices[1].Position,x+w/2,y-h/2,0);
  setVec3(vertices[2].Position,x-w/2,y-h/2,0);
  setVec3(vertices[3].Position,x-w/2,y+h/2,0);
  va->vertices = vertices;
  va->vertices_Size = 4;
  unsigned * it=(unsigned*)malloc(sizeof(unsigned)*6);
  it[0]=0;it[1]=1;it[2]=3;
  it[3]=1;it[4]=2;it[5]=3;
  Index_array * ia = (Index_array*)malloc(sizeof(Index_array));
  ia->indices = it;
  ia->indices_Size = 6;
  Texture_array * ta = (Texture_array*)malloc(sizeof(Texture_array));
  ta->textures = NULL;
  ta->textures_Size = 0;
  return interface_Mesh(shader,va,ia,ta);
end
