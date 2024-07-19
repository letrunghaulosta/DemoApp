#include <iostream>
#include "TaskManagement.h"
#include <chrono>
#include <thread>
#include <unistd.h>
#include <string>
#include <sys/select.h>
#include <fcntl.h>

void test1(void);
void test2(void);
void test3(void);


bool TEST = false;

void mainTask(TaskManagement* taskMgmt)
{
   fd_set set;
   std::string a;
   FD_ZERO(&set);
   FD_SET(STDIN_FILENO, &set);

   timeval timeout = {0, 1000};

   int flags = fcntl(STDIN_FILENO, F_GETFL);

   fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

   int result = select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout);

   fcntl(STDIN_FILENO, F_SETFL, flags);

   while(!TEST)
   {
      if(result > 0 && FD_ISSET(STDIN_FILENO, &set))
      {
         std::cout << "\x1B[2J\1x1B[?47h\n";
         std::cout << "Select below: " << std::endl;
         std::cout << "1 - Run\n";
         std::cout << "2 - Stop\n";
         std::cout << "3 - Exit\n";

         std::vector<std::string> select;
         std::getline(std::cin, a);

         while(!a.empty())
         {
            select.push_back(s);
         }

         switch(std::stoi(select[0])) 
         {
            case 1:
            taskMgmt->Run(select[1]);
            break;
            case 3:
            TEST = true;
            break;
         }
      }
   }
}

int main()
{
   auto start_time = std::chrono::high_resolution_clock::now();
   auto stop_time = std::chrono::high_resolution_clock::now();
   auto running_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

   TaskManagement TaskMgmt;



   TaskMgmt.RegisterTask("TEST1", test1, 3000);
   TaskMgmt.RegisterTask("TEST2", test2, 30000);
   TaskMgmt.RegisterTask("TEST3", test2, 300);

   std::cout << "First LIST" << std::endl;
   TaskMgmt.List();

   TaskMgmt.Run("TEST1");

   std::thread t1(&TaskManagement::Process, &TaskMgmt);
   std::thread t2(mainTask, &TaskMgmt);


   do
   {
      if(0 == running_time.count() % 100)
      {
         // std::cout << "TIMESTAMP: " << running_time.count() << std::endl;;
      }
      usleep(10000);
      std::cout << "\x1B[2J\x1B[H" << std::endl;
      TaskMgmt.List();
      std::cout << "\1x1B[?47h";
      stop_time = std::chrono::high_resolution_clock::now();
      running_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

   }while(TEST == false);

   t1.join();
   t2.join();

   std::cout << "TIMESTAMP: " << running_time.count() << std::endl;;
   std::cout << "END TIME: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - std::chrono::high_resolution_clock::time_point()).count() << std::endl;;

   std::cout << "LAST LIST" << std::endl;
   TaskMgmt.List();
   return 0;
}

void test1(void)
{
   std::cout << "TEST 1 DONE" << std::endl;
}

void test2(void)
{
   std::cout << "TEST 2 DONE" << std::endl;
}

void test3(void)
{
   std::cout << "TEST 3 DONE" << std::endl;
}