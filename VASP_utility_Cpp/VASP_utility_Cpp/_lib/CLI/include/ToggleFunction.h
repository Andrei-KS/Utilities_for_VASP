#ifndef __TOGGLEFUNCTION_H__
#define __TOGGLEFUNCTION_H__

#include "CalledPanelFunction.h"

/**
* This class bind with boolean variable for toggle it
* when call execute function of this class
* 
* @see CalledPanelFunction
* @author Andrei-KS
*/
class ToggleFunction : public CalledPanelFunction
{
public:
	/**
	* When construct this class boolean variable is bonded with it
	* @param toggleableParameter - this parameter will bonded to the object
	*/
	ToggleFunction(bool* toggleableParameter);

	/**
	* Toggle bonded boolean variable to the opposite value
	*/
	virtual void execute() override;

private:
	/** Pointer to bonded with this object boolean variable */
	bool* itsToggleableParameter;
};

#endif // !__TOGGLEFUNCTION_H__