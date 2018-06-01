#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>

using int32 = int;

namespace JJHexagon {
	///Information describing a 2D point on the grid; i.e., a Hexagon's center, vertices, or edges.
	struct PointData
	{
		const float X;
		const float Y;

		PointData(int32 newX, int32 newY) : X(newX), Y(newY) {}
	};

	///Information describing a cubic Hexagon. 
    struct HexData
	{
		///Describes the 'x' and 'y' coordinates of a Hexagon on a grid.
		PointData Position;

		///Describes which stacked grid the Hexagon belongs to.
		int32 Layer;

		HexData(PointData newPos, int32 newLayer) : Position(newPos), Layer(newLayer) {}
	};

	PointData AddPointData(PointData a, PointData b)
	{
		return PointData(a.X + b.X, a.Y + b.Y);
	}

	PointData ScalePointData(PointData a, float scale)
	{
		return PointData(a.X * scale, a.Y * scale);
	}

	float GetZ(PointData hexPos)
	{
		return hexPos.X + hexPos.Y;
	}

	float GetZ(HexData hexData)
	{
		return hexData.Position.X + hexData.Position.Y;
	}

	HexData GetNeighbour(HexData origin, PointData posOffset, int32 layerOffset) {
		return HexData(AddPointData(origin.Position, posOffset), origin.Layer + layerOffset);
	}

	/*PointData GetVertex(PointData origin, int32 i) {
		float degrees = 60 * i - 30;
		float radians = M_PI / 180 * degrees;
		return PointData(origin.X + cos(radians),
				origin.Y + sin(radians));
	}

	PointData GetVertex(HexData hexData, int32 i) {
		float degrees = 60 * i - 30;
		float radians = M_PI / 180 * degrees;
		return PointData(hexData.Position.X + cos(radians),
			hexData.Position.Y + sin(radians));
	}

	PointData GetEdge() {

	}*/

    float GetDistanceBetween(HexData hexA, HexData hexB) {
		return std::max(
			std::max(std::abs(hexB.Position.X - hexA.Position.X), std::abs(hexB.Position.Y - hexA.Position.Y)),
			std::abs(GetZ(hexB.Position) - GetZ(hexA.Position)));
	}
}