#ifndef ACTIONWATCHER_H
#define ACTIONWATCHER_H

#include "pluginactionprogress.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QObject>

/**
  * @brief The PluginActionWatcher class watches and controls asynchronous plugin execution
  *
  * \see PluginAction PluginActionProgress
*/
template<class T>
class Q_DECL_EXPORT PluginActionWatcher
{
public:
    explicit PluginActionWatcher(QFuture<T> future,
                                    QSharedPointer<PluginActionProgress> progress,
                                    bool delayWatcherSet = false) :
        m_progress(progress)
    {
        m_future = future;
        if (!delayWatcherSet) {
            m_futureWatcher.setFuture(future);
        }
    }

    T result()
    {
        return m_future.result();
    }

    QSharedPointer<PluginActionProgress> progress()
    {
        return m_progress;
    }

    QFutureWatcher<T>* watcher()
    {
        return &m_futureWatcher;
    }

    /// If the watcher set was delayed to allow for race-safe connections, it can be set with this method
    void setFutureInWatcher()
    {
        m_futureWatcher.setFuture(m_future);
    }

private:
    QFuture<T> m_future;
    QFutureWatcher<T> m_futureWatcher;
    QSharedPointer<PluginActionProgress> m_progress;
};

#endif // ACTIONWATCHER_H
