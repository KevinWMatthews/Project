#ifndef Test_Array_H_
#define Test_Array_H_

class Test_Array
{
  public:
    explicit Test_Array();
    virtual ~Test_Array();

  private:
    Test_Array(const Test_Array&);
    Test_Array& operator=(const Test_Array&);
};

#endif
