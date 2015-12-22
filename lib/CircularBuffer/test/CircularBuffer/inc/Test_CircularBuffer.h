#ifndef Test_CircularBuffer_H_
#define Test_CircularBuffer_H_

class Test_CircularBuffer
{
  public:
    explicit Test_CircularBuffer();
    virtual ~Test_CircularBuffer();

  private:
    Test_CircularBuffer(const Test_CircularBuffer&);
    Test_CircularBuffer& operator=(const Test_CircularBuffer&);
};

#endif
