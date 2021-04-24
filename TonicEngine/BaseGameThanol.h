#pragma once
namespace dae
{
	class BaseGameThanol
	{
	public:
		BaseGameThanol() = default;
		~BaseGameThanol() = default;
		BaseGameThanol(const BaseGameThanol& g) = delete;
		BaseGameThanol(BaseGameThanol&& g) = delete;
		BaseGameThanol& operator=(const BaseGameThanol& g) = delete;
		BaseGameThanol& operator=(BaseGameThanol&& g) = delete;

		virtual void CreateGameScenes() = 0;
	};

}

