#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include "Defines/DVideoModes.h"
#include "Defines/ResourceIDS.h"

class Resource
{
	private:

	public:
		Resource();
		~Resource();

		std::string getItem( E_RESOLUTION_TYPE rt_type, E_RES_TYPE res_type, E_RES_ID res_id );
};

#endif