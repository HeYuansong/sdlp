#include <font.h>

def(static void ,setVec3,vec3 vector,float x,float y,float z)
  vector[0] = x;
  vector[1] = y;
  vector[2] = z;
end

def(static void,setVec2,vec3 vector,float x,float y)
  vector[0] = x;
  vector[1] = y;
end

def(Mesh * , interface_Font ,unsigned * shader , wchar_t font, float x, float y, float size, vec3 color)

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

interface(Character)
  GLuint TextureID;
  int Size[2];
  int Bearing[2];
  GLuint Advance;
ends

mat4x4 projection;
glUseProgram(*shader);
mat4x4_ortho(projection, 0, 1280, 0, 720, 0, 100);
glUniformMatrix4fv(glGetUniformLocation(*shader, "projection"), 1, GL_FALSE, &projection[0][0]);

FT_Library ft;
if (FT_Init_FreeType(&ft))
  printf("ERROR::FREETYPE: Could not init FreeType Library");
FT_Face face;
if (FT_New_Face(ft, "fonts/FZXKTJW.TTF", 0, &face))
  printf("ERROR::FREETYPE: Failed to load font");
FT_Set_Pixel_Sizes(face, 0, size);
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

if(FT_Load_Char(face, font, FT_LOAD_RENDER))
  printf("ERROR::FREETYTPE: Failed to load Glyph");

GLuint texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(
	     GL_TEXTURE_2D,
	     0,
	     GL_RED,
	     face->glyph->bitmap.width,
	     face->glyph->bitmap.rows,
	     0,
	     GL_RED,
	     GL_UNSIGNED_BYTE,
	     face->glyph->bitmap.buffer
	     );
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

Character ch = body
  texture,
  body
    face->glyph->bitmap.width,
    face->glyph->bitmap.rows
  end,
  body
    face->glyph->bitmap_left,
    face->glyph->bitmap_top
  end,
  face->glyph->advance.x
ends

FT_Done_Face(face);
FT_Done_FreeType(ft);

glUseProgram(*shader);
glUniform3f(glGetUniformLocation(*shader, "textColor"), color[0], color[1], color[2]);
GLfloat xpos = x + ch.Bearing[0] ;
GLfloat ypos = y - (ch.Size[1] - ch.Bearing[1]);
GLfloat w = ch.Size[0] ;
GLfloat h = ch.Size[1] ;

Vertex_array * va = (Vertex_array*)malloc(sizeof(Vertex_array));
Vertex * vertices = (Vertex*)malloc(sizeof(Vertex)*4);

setVec3(vertices[0].Position, xpos,     ypos + h, 0);
setVec3(vertices[1].Position, xpos,     ypos,     0);
setVec3(vertices[2].Position, xpos + w, ypos,     0);
setVec3(vertices[3].Position, xpos + w, ypos + h, 0);
setVec2(vertices[0].TexCoords, 0.0, 0.0);
setVec2(vertices[1].TexCoords, 0.0, 1.0);
setVec2(vertices[2].TexCoords, 1.0, 1.0);
setVec2(vertices[3].TexCoords, 1.0, 0.0);

va->vertices = vertices;
va->vertices_Size = 4;


unsigned * it=(unsigned*)malloc(sizeof(unsigned)*6);


it[0]=0;it[1]=1;it[2]=2;
it[3]=0;it[4]=2;it[5]=3;


Index_array * ia = (Index_array*)malloc(sizeof(Index_array));


ia->indices = it;
ia->indices_Size = 6;


Texture_array * ta = (Texture_array*)malloc(sizeof(Texture_array));

Texture * textures = (Texture*)malloc(sizeof(Texture));

textures[0].id = texture;

sprintf(textures[0].type,"texture_text");

ta->textures = textures;
ta->textures_Size = 1;
return interface_Mesh(shader,va,ia,ta);

end
