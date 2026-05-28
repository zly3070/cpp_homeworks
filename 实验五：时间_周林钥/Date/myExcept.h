#ifndef MYEXCEPT_HEADER
#define MYEXCEPT_HEADER
//-------------------------------------
class MyExcept{  // 自定义异常接口，接受抛出的异常
public:
  virtual char* getWhat() = 0;
};//-----------------------------------
class MyFormatError : public MyExcept{
public:
  char* getWhat(){ return "Format Error."; }
};//-----------------------------------
class MyIllegal : public MyExcept{
public:
  char* getWhat(){ return "Illegal."; }
};//-----------------------------------
#endif  //MYEXCEPT_HEADER
