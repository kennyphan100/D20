#pragma once
#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "Map.h"
#include "Campaign.h"

using namespace std;

class Editor {
	public:
		Editor();
		bool runEditor();
	private:
		vector<Map> maps; ///< Maps included in the campaign

		void createMap();
		Map* selectMap();
		void editMap();
		void displayCurrentMap();
		void createCampaign();
		void editCampaign();
		void displayAllMaps();
		int countMapFiles(const string& directoryPath);
		void saveToFile();
		void saveMapToFile();
		void saveCampaignToFile();
		void loadMapFromFile();
		void loadCampaignFromFile();
		//void verifytAndSave();
};

#endif
