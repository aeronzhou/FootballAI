#include "PlayerPositionManager.h"
#include "ParamLoader.h"

#include <QtXml/QtXml>

void PlayerPositionManager::printRegions()
{
	int n = Prm.NumRegionsVertical;
	int m = Prm.NumRegionsHorizontal;
	int cnt = 0;

	FILE* pfile = fopen("./../data/xml/Regions.txt", "w");

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (j == m / 2)
				fprintf(pfile, "|%2d| ", cnt++);
			else 
				fprintf(pfile, "%2d%c", cnt++, j == m - 1 ? '\n' : ' ');
		}
	}

	fclose(pfile);
}

PlayerPositionManager& PlayerPositionManager::get()
{
	static PlayerPositionManager instance;
	return instance;
}

std::vector<int> PlayerPositionManager::getAssignedPosition(const QString& state_type)
{
	return mPositionMap[state_type];
}

PlayerPositionManager::PlayerPositionManager()
{
	// Printf all regions with numbers
	printRegions();

	const QString path = "./../data/xml/PlayerPosition.xml";

	QFile file(path);
	QDomDocument doc;

	if (!file.open(QIODevice::ReadOnly)) 
	{
		dt::Logger::get().error("Couldn't open file " + path);
	} 
	else if (doc.setContent(&file)) 
	{
		// Create param table
		QDomElement root = doc.documentElement();

		for (QDomElement child = root.firstChildElement(); 
			!child.isNull(); child = child.nextSiblingElement()) 
		{
			// State
			QString state_name = child.nodeName();
			QDomElement red_team = child.firstChildElement();
			QDomElement blue_team = red_team.nextSiblingElement();
			std::vector<int> vec_pos;

			QDomElement it = red_team.firstChildElement();
			QString comm;
			for (int i = 0; i < 7; ++i)
			{
				vec_pos.push_back(it.text().toInt());	
				it = it.nextSiblingElement();
			}

			it = blue_team.firstChildElement();
			for (int i = 0; i < 7; ++i)
			{
				vec_pos.push_back(it.text().toInt());
				it = it.nextSiblingElement();
			}

			mPositionMap[state_name] = vec_pos;
		}
	}
}

