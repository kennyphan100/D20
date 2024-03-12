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
		void createCampaign();
		Campaign* selectCampaign();
		void editCampaign();
		Map* selectMapInCampaign(const string& campaignName, const string& call);
		void displayAllMaps();
		void displayAllCampaigns();
		void displayAllMapsInCampaign(const string& campaignName);
		int countMapFiles(const string& directoryPath);
};

#endif
