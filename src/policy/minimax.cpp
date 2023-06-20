#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

typedef struct Node{
  int value;
  int which;
}Node;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Node minimax(State* node,int depth){
  node->get_legal_actions();
  int value = 0;
  int player = node->player;
  Node tmp;
  if(depth == 0 || node->legal_actions.empty()){
    tmp.value = node->evaluate();
    tmp.which = 0;
    return tmp;
  }
  if (!player){
    value = -100000;
    //for(auto t: node->legal_actions){
    for(int t=0;t<node->legal_actions.size();t++){
      State* child = node->next_state(node->legal_actions[t]);
      int nextvalue = minimax(child,depth-1).value;
      if(nextvalue > value){
        value = nextvalue;
        tmp.which = t;
      }  
    }
    tmp.value = value;
  }
  if(player){
    value = 100000;
    //for(auto t: node->legal_actions){
    for(int t=0;t<node->legal_actions.size();t++){
      State* child = node->next_state(node->legal_actions[t]);
      int nextvalue = minimax(child,depth-1).value;
      if(nextvalue < value){
        value = nextvalue;
        tmp.which = t;
      }  
    }
    tmp.value = value;
  }
  return tmp;
}

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  //int value;
  //int which;
  //int nv;
  //int t = minimax(state->next_state(actions[0]),depth).which;
  int t = minimax(state,depth).which;

  /*for(int i=0;i<actions.size();i++){
    nv = minimax(state->next_state(actions[i]),depth,p);
    if(p == 0){
      if(nv > value){
        value = nv;
        which = i;
      }
    }
    else{
      if(nv < value){
        value = nv;
        which = i;
      }
    }
     
  }*/
  return actions[t];
}
