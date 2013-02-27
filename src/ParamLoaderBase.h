#ifndef FOOTBALL_AI_PARAM_LOADER
#define FOOTBALL_AI_PARAM_LOADER

#include <Scene/Node.hpp>

#include <QtXml/QtXml>

#include <map>


class ParamLoaderBase 
{

public:
	typedef std::map<QString, QString> MSS;

	bool readFile(const QString& path, MSS& param_table)
	{
		param_table.clear();
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
			param_table.clear();

			for (QDomElement child = root.firstChildElement(); 
				!child.isNull(); child = child.nextSiblingElement()) 
			{
				param_table[child.nodeName()] = child.text();
			}

			return true;
		}

		return false;
	}

};

#endif