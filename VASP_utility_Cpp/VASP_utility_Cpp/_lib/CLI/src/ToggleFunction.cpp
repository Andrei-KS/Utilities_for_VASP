#include "..\include\ToggleFunction.h"


#include "ToggleFunction.h"

ToggleFunction::ToggleFunction(bool* toggleableParameter)
	: itsToggleableParameter(toggleableParameter)
{
}

void ToggleFunction::execute()
{
	(*itsToggleableParameter) = !(*itsToggleableParameter);
}
