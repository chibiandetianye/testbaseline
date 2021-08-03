#ifndef _TESTBASE_INCLUDE_H_
#define _TESTBASE_INCLUDE_H_

#include<sys/time.h>
#include<stdint.h>

#include<ostream>

class TESTBase{
public:
    TESTBase()=default;
    virtual ~TESTBase() = default;

    virtual void runBaseline(ostream& )=0;

protected:
    inline uint64_t getTime(){
        struct timeval time = gettimeofday();
        return static_cast<int>(time.tv_sec*1000000 + time.tv_usec);
    }
private:
};

#endif /** _TESTBASE_INCLUDE_H_ */