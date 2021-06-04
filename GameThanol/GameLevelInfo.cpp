#include "GameLevelInfo.h"
#include <rapidjson.h>
#include <document.h>
#include <filereadstream.h>

GameLevelInfo::GameLevelInfo(const std::wstring& filepath)
	: m_LevelInfo()
	, m_QBertInfo()
{
	ParseLevelFile(filepath);
}

void GameLevelInfo::ParseLevelFile(const std::wstring& filepath)
{
	const wchar_t* input = filepath.c_str();
	FILE* pIFile = nullptr;
	_wfopen_s(&pIFile, input, L"r");

	if (pIFile != nullptr)
	{
		fseek(pIFile, 0, SEEK_END);
		size_t size = ftell(pIFile);
		fseek(pIFile, 0, SEEK_SET);

		char* buffer = new char[size];

		rapidjson::FileReadStream stream(pIFile, buffer, size);
		rapidjson::Document doc;
		doc.ParseStream(stream);

		//Parse level info
		const rapidjson::Value& LevelLayer = doc["Level"];
		m_LevelInfo.GridSize = LevelLayer["GridSize"].GetInt();
		m_LevelInfo.NbVisits = LevelLayer["NbVisits"].GetInt();
		m_LevelInfo.IsAlternating = LevelLayer["IsAlternating"].GetBool();

		auto disks = LevelLayer["Disks"].GetArray();
		for (auto diskIt = disks.Begin(); diskIt != disks.End(); ++diskIt)
		{
			const rapidjson::Value& diskLayer = *diskIt;

			HexCoordinate hc{};
			hc.Row = diskLayer["RowCoordinate"].GetInt();
			hc.Col = diskLayer["ColCoordinate"].GetInt();
			m_LevelInfo.DiskCoordinates.push_back(hc);
		}

		//Parse QBert info
		const rapidjson::Value& QBertLayer = doc["QBert"];
		int jumpTimeMS = QBertLayer["JumpTimeMS"].GetInt();
		m_QBertInfo.JumpTime = float(jumpTimeMS) / 1000.f;
		m_QBertInfo.Health = QBertLayer["Health"].GetInt();

		//Clean buffer
		delete[] buffer;
		fclose(pIFile);
	}
}
