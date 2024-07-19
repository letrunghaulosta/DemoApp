#ifndef _UNIT_H_
#define _UNIT_H_

typedef enum
{
   JOB_FOREST,
   JOB_LIMIT
}  JobType;

class Job
{
public:
   int getExp(){return exp;}
   int getPace(){return pace;}
private:
   JobType type;
   int exp;
   int pace;
};

#endif