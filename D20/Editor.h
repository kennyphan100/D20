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
		void runEditor();
	private:
		map<string, Map> maps; ///< Maps included in the campaign, keyed by their names

		void createMap();
		Map* selectMap();
		void editMap();
		void displayCurrentMap();
		void createCampaign();
		void editCampaign();
		void displayAllMaps();
		void saveMapToFile();
		void saveCampaignToFile();
		void loadMapFromFile();
		void loadCampaignFromFile();
		//void verifytAndSave();
};

#endif
