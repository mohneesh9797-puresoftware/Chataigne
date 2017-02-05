/*
  ==============================================================================

    AutomationEditor.h
    Created: 5 Feb 2017 2:58:27pm
    Author:  Ben

  ==============================================================================
*/

#ifndef AUTOMATIONEDITOR_H_INCLUDED
#define AUTOMATIONEDITOR_H_INCLUDED

#include "InspectableEditor.h"
#include "AutomationUI.h"

class AutomationEditor :
	public InspectableEditor
{
public:
	AutomationEditor(Automation * automation, bool isRoot);
	~AutomationEditor();

	ScopedPointer<AutomationUI> automationUI;

	void resized() override;
};



#endif  // AUTOMATIONEDITOR_H_INCLUDED
