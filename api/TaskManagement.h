#ifndef _TASK_H_
#define _TASK_H_

#include <memory>
#include <vector>
#include <chrono>
#include <iostream>

class TaskType
{
public:
TaskType(std::string name, void(*func)(void), int interval){
   this->name = name;
   this->funcCall = func;
   this->interval = interval;
   this->isActive = false;
   this->startTime = std::chrono::high_resolution_clock::now();
}
   std::string GetName(){return name;}
   int GetRemainTime(){
      return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
   }
   int GetInterval(){return interval;}

   void Ckb(){if(funcCall != nullptr) funcCall();}
   void Start(){
      SetActivate(true);
      startTime = std::chrono::high_resolution_clock::now();
   }
   bool IsActive(){return isActive;}
   void SetActivate(bool state){isActive = (state == true)?true:false;}
private:
   std::string name;
   void(*funcCall)(void);
   int interval;
   std::chrono::_V2::system_clock::time_point startTime;
   bool isActive;
};

class TaskManagement
{
public:
   TaskManagement(){
      taskCount = 0;}
   void RegisterTask(std::string name, void(*func)(void), int interval);
   void Process(void);
   void Done(TaskType* task);
   void Stop(std::string name);
   void Run(std::string name);
   void List();
private:
   std::vector<std::shared_ptr<TaskType>> task;
   int taskCount;
};

#endif