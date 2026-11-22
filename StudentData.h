#pragma once

#include <string>
#include "BuildConfig.h"

#ifdef PRE_RELEASE

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
    std::string emailId;
};

#else

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
};

#endif
