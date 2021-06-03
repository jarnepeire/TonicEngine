#pragma once
struct HexCoordinate
{
	HexCoordinate()
		: Row(0), Col(0) {}

	HexCoordinate(int r, int c)
		: Row(r), Col(c) {}

	HexCoordinate(const HexCoordinate& hc)
		: Row(hc.Row), Col(hc.Col) {}

	bool operator==(const HexCoordinate& hc) const
	{
		return (this->Row == hc.Row && this->Col == hc.Col);
	}

	int Row;
	int Col;
};