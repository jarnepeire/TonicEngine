#pragma once
#include <string>
#include "HexCoordinate.h"
#include <vector>

struct LevelInfo
{
	int GridSize = {};
	int NbVisits = {};
	bool IsAlternating = {};
	std::vector<HexCoordinate> DiskCoordinates;
};

struct QBertInfo
{
	float JumpTime;
	int Health;
};

class GameLevelInfo
{
public:
	GameLevelInfo(const std::wstring& filepath);

	const LevelInfo& GetLevelInfo() const { return m_LevelInfo; }
	const QBertInfo& GetQBertInfo() const { return m_QBertInfo; }

private:
	LevelInfo m_LevelInfo;
	QBertInfo m_QBertInfo;

	void ParseLevelFile(const std::wstring& filepath);
};

