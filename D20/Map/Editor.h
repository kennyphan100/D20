//! @file 
//! @brief Header file for Editor.cpp
//!

#pragma once
#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "Map.h"
#include "Campaign.h"

using namespace std;

/**
 * @class Editor
 * @brief Class for managing map and campaign editing.
 *
 * The Editor class provides functionality to create, edit, and manage maps and campaigns.
 * It allows users to create new maps, edit existing maps, create campaigns, edit campaigns,
 * and perform various operations related to map and campaign management. Editor instances
 * maintain a collection of maps and facilitate interactions with them within the context of campaigns.
 *
 * Design:
 * Editor encapsulates functionality for map and campaign editing in a cohesive manner.
 * It utilizes vectors to store maps and provides methods for creating, selecting, and editing maps
 * within the collection. Additionally, it facilitates campaign creation, selection, and editing
 * by utilizing Campaign objects. The design promotes modularity and extensibility, enabling
 * straightforward addition of new editing features in the future.
 *
 * Dependencies:
 * The class depends on the Map and Campaign classes for map and campaign management.
 */
class Editor : public Observable {
	public:
		Editor();
		bool runEditor();
		void createMapGUI(string name, int width, int height);
		void createCampaignGUI(string campaignName, std::vector<std::string> selectedMaps);
		void editMapGUI(Map* map);
		Map* selectMapGUI(string mapName);
		Map* selectMap();
		Campaign* selectCampaignGUI(string campaignName);
		void editCampaignGUI(Campaign* campaign, const vector<string>& selectedMaps);
		Character* selectCharacterGUI(string mapName);

	private:
		vector<Map> maps; ///< Collection of maps included in the campaign.

		//void createMap();
		void createMap();
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
