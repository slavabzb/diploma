#include "Logger.h"



Logger* Logger::getInstance()
{
  static Logger instance;
  
  return &instance;
}



