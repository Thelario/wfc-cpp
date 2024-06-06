#pragma once

#include <string>

#include "GameObject.h"

namespace Satellite
{
	class Utils
	{
		public:
			static const std::string CurrentDateTimeToString();
			static const std::string GetTagName(ColliderTag tag);
	};
}