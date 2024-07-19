#include "TaskManagement.h"
#include <chrono>
#include <iostream>
#include <string.h>

extern bool TEST;

std::string printString(int times,std::string str)
{
   std::string result = "";
   for(int i=0;i<times;i++)
   {
      result += str;
   }
   return result;
}

void TaskManagement::RegisterTask(std::string name, void(*func)(void), int interval)
{
   this->task.push_back(std::shared_ptr<TaskType>(new TaskType(name, func, interval)));
   taskCount++;
   std::cout << "Registered: " << name << std::endl;
}

void TaskManagement::Process()
{
   while(!TEST)
   {
   for(auto it : task)
   {
      TaskType *task = it.get();
      if(true == task->IsActive())
      {
         if(task->GetRemainTime() >= task->GetInterval())
         {
            this->Done(task);
         }
      }
   }
   }
}

void TaskManagement::Done(TaskType* task)
{
   std::cout << "Task: <" << task->GetName() << "> completed." << std::endl;
   task->Start();
}

void TaskManagement::Run(std::string name)
{
   for(auto it : task)
   {
      TaskType *task = it.get();
      if(task->GetName() == name)
      {
         task->Start();
         return;
      }
   }

   std::cout << "fail to find: " << name << std::endl;

}

void TaskManagement::Stop(std::string name)
{

}

void TaskManagement::List()
{
   std::cout << "Name\t" << "Activated\t" << "Interval\t" << "Remaining Time" << std::endl;
   for(auto it : task)
   {
      auto remainTime = it.get()->GetRemainTime();
      auto Interval = it.get()->GetInterval();
      std::cout << it.get()->GetName() << "\t" << it.get()->IsActive() << "\t\t";
      if(it.get()->IsActive())
      {
         std::cout << it.get()->GetInterval() << "\t\t|" << printString((remainTime*20/Interval),"\x1B[48;5;82m ") << printString((20 - remainTime*20/Interval),"\x1B[0m ") << "|" << std::endl;
      }
      else
      {
         std::cout << it.get()->GetInterval() << "\t\t|" << printString(20,"\x1B[0m ") << "|" << std::endl;
      }
      
   }
}