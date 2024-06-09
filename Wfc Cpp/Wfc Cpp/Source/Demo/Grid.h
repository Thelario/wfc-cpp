#pragma once

namespace Demo
{
	class Grid
	{
		private:
			int max_width = 10;
			int max_height = 8;

		public:
			static Grid* Instance();

			void CreateGrid();
	};
}