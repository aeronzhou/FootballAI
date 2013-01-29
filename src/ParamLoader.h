#ifndef FOOTBALL_AI_PARAM_LOADER
#define FOOTBALL_AI_PARAM_LOADER

#include <Scene/Node.hpp>

#include <QtXml/QtXml>

#include <map>


class ParamLoader 
{

public:
	typedef std::map<QString, QString> MSS;

	ParamLoader() 
	{
		mParamTables = MSS();	
	}

	bool setParmFile(QString path) 
	{
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
			mParamTables.clear();

			for (QDomElement child = root.firstChildElement(); 
				!child.isNull(); child = child.nextSiblingElement()) 
			{
				mParamTables[child.nodeName()] = child.text();
			}

			return true;
		}

		return false;
	}

	MSS getParamTable() 
	{
		return mParamTables;
	}

private:

	MSS mParamTables;  //
};

#endif