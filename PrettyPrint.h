#pragma once

#include "BuildConfig.h"
#include "StudentData.h"

#ifdef PRE_RELEASE

#include <string>
#include <vector>

std::string FormatStudents(std::vector<STUDENT_DATA> students);
void PrettyPrint(std::vector<STUDENT_DATA> students);

#endif
