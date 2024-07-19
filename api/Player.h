#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Unit.h"

class Player
{
public:
private:
   
};

class PlayerJob
{
public:
   void setLevel(int lv){curLv = lv;}
   void incLevel(){curLv++;}
   void setCurrentExp(int exp);
   void incCurrentExp(int exp){curExp +=exp;}
   void setMaxExp(int exp){maxExp = exp;}
   JobType getJobType(){return jobType;}
   int getLevel(){return curLv;}
   int getCurrentExp(){return curExp;}
   int getMaxExp(){return maxExp;}
private:
   JobType  jobType;
   int curLv;
   int curExp;
   int maxExp;
};

#endif