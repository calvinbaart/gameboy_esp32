#ifndef _MEMORY_CONTROLLER_H_
#define _MEMORY_CONTROLLER_H_

class IMemoryController
{
public:
    virtual long read(long position) = 0;
    virtual void write(long position, long value) = 0;
};

#endif