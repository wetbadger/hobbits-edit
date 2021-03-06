#ifndef PLUGINACTION_H
#define PLUGINACTION_H

#include "pluginactionwatcher.h"
#include "analyzerrunner.h"
#include "hobbitspluginmanager.h"
#include "parameters.h"
#include <QtConcurrent/QtConcurrentRun>
#include "hobbits-core_global.h"

class BitContainerManager;

/**
  * @brief The PluginAction class describes a reproduceable plugin action
  *
  * PluginActions can be used to document, de/serialize, and reproduce actions that plugins can
  * take.
  *
  * The plugin action system is similar to the "Command" design pattern. The PluginAction
  * class correlates loosely to the state of the ConcreteCommand class in that pattern.
  *
  * \see PluginActionManager PluginActionLineage PluginActionBatch
*/
class HOBBITSCORESHARED_EXPORT PluginAction
{
public:
    enum HOBBITSCORESHARED_EXPORT PluginType {
        Framer = 1 /*Deprecated*/,
        Operator = 2,
        Analyzer = 3,
        Importer = 4,
        Exporter = 5,
        NoAction = 6
    };

    PluginAction(PluginType pluginType, QString pluginName, Parameters parameters);

    static QSharedPointer<PluginAction> createAction(PluginType pluginType, QString pluginName, const Parameters &parameters);
    static QSharedPointer<PluginAction> analyzerAction(QString pluginName, const Parameters &parameters);
    static QSharedPointer<PluginAction> operatorAction(QString pluginName, const Parameters &parameters);
    static QSharedPointer<PluginAction> importerAction(QString pluginName, const Parameters &parameters = Parameters::nullParameters());
    static QSharedPointer<PluginAction> exporterAction(QString pluginName, const Parameters &parameters = Parameters::nullParameters());
    static QSharedPointer<PluginAction> noAction();

    PluginType pluginType() const;
    QString pluginName() const;
    Parameters parameters() const;

    int minPossibleInputs(QSharedPointer<const HobbitsPluginManager> pluginManager) const;
    int maxPossibleInputs(QSharedPointer<const HobbitsPluginManager> pluginManager) const;

    QJsonObject serialize() const;
    static QSharedPointer<PluginAction> deserialize(QJsonObject data);

    inline bool operator==(const PluginAction &other) const
    {
        return (
            m_pluginName == other.pluginName()
            && m_pluginType == other.pluginType()
            && m_parameters == other.parameters()
            );
    }

private:
    PluginType m_pluginType;
    QString m_pluginName;
    Parameters m_parameters;
};


inline uint qHash(const PluginAction &key, uint seed)
{
    return qHash(key.parameters().values(), seed) ^ uint(key.pluginType()) ^ qHash(key.pluginName(), seed);
}

#endif // PLUGINACTION_H
