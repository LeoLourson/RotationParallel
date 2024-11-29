#pragma once
#include <string.h>
#include <cstdlib>

enum errorcodes {
    EC_NORM =  0,
    EC_BADARG = -1,
    EC_BADOPEN = -2,
    EC_BADINPUT = -3,
    EC_MEM = -4,
    EC_BADDATA = -5,
    EC_ZERO = -6,

};

class MyException
{
public:
    MyException(const char* msg, enum errorcodes errorcode) {
    	strncpy(message, msg, 255); //внимание 255 и нужен инклуд
    	ERROR = errorcode; 
    }
    
    const char* what() const noexcept {
        return message;
    }
    enum errorcodes Code() const {return ERROR; }
    
private:
    char message[256];    // сообщение об ошибке
    enum errorcodes ERROR;
};

/*
catch (std::bad_alloc) { throw new MyException("StackList<TYPE>::push: memory allocation error\n", EC_MEM); }
};
*/


