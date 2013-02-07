#ifndef FOOTBALL_AI_PARAM_LOADER
#define FOOTBALL_AI_PARAM_LOADER

#include <Scene/Node.hpp>

#include <QtXml/QtXml>

#include <map>


class ParamLoaderBase 
{

public:
	typedef std::map<QString, QString> MSS;

	ParamLoaderBase(const QString& path)
	{
		mParamTables = MSS();
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

			mIsGoodFile = true;
		}
	
		mIsGoodFile = false;
	}

protected:
	bool mIsGoodFile; 
	MSS mParamTables;  //!< Table to store params
};

#endif