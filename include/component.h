#include <mesh.h>

interface(Component)
  ComponentNode * node;
  DataModel * dm;
  MeshTable * table;
  void (*eventCallBack)(Component*,char * data);
ends
