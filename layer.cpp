#include "layer.h"

Layer::Layer(QVector<unsigned> contigSizes, QVector<QString> contigNames)
{
	qDebug() << "layer created";
	for(unsigned i = 0; i < contigNames.size(); ++i)
	{
		QString name = contigNames[i];
		contigs[name] = ContigData();
		size[name] = contigSizes[i];
	}
}

bool Layer::addMatch(QString precName, QString prodName, unsigned precU, 
			  unsigned precD, unsigned prodU, unsigned prodD)
{

	ContigData *precContig = &contigs[precName];
	int precPos = precContig->checkPosition(precU, precD);
	
	ContigData *prodContig = &contigs[prodName];
	int prodPos = prodContig->checkPosition(prodU, prodD);
	
	if( (precPos == -1) || (prodPos == -1) ) return false;
	
	precContig->include(precU, precD, precPos);
	prodContig->include(prodU, prodD, prodPos);
	
	return true;

}

void Layer::print()
{
 	QMap<QString, ContigData>::iterator i = contigs.begin();
	
	while (i != contigs.end()) {
    	qDebug() << i.key() << ": "; 
    	(i.value()).print();
    	++i;
 	}
}