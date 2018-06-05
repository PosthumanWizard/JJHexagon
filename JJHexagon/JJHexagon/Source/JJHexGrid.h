#pragma once
#include <vector>;

namespace JJHexagon {
	class JJHexGrid
	{
	public:
		JJHexGrid();
		~JJHexGrid();
	private:
		
		std::vector<std::vector<HexData>> hexLayers;
	};
}

