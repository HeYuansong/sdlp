#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>



#define def(retp, name, args...)			\
  retp name(args){
#define times(number)			\
  for(int i=0;i<number;i++){
#define fromto(from,to)\
  for(int i=from;i<to;i++){
#define forint(from,to,dlt)\
  for(int i=from;i<to;i+=dlt){
#define when(condi)\
  while(condi){
#define cond(condi)\
  if(condi){
#define esif(condi)\
  else if(condi){
#define deft\
  else{

#define body {
#define end }
#define ends };

#define interface(NAME) typedef struct NAME NAME;struct NAME{
