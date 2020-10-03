#pragma once
#ifndef _CLASS_PROCESS_HELP_
#define _CLASS_PROCESS_HELP_

#include "Process.h"

class Help : public Process {
	public:
		void execute(vector<string>) const override;
};

#endif _CLASS_PROCESS_HELP_