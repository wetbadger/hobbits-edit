#include "importresult.h"

ImportResult::ImportResult()
{

}

ImportResult* ImportResult::setContainer(QSharedPointer<BitContainer> container)
{
    m_container = container;
    return this;
}

QSharedPointer<BitContainer> ImportResult::getContainer() const
{
    return m_container;
}

ImportResult* ImportResult::setParameters(const Parameters &parameters)
{
    m_parameters = parameters;
    return this;
}

const Parameters ImportResult::parameters() const
{
    return m_parameters;
}

bool ImportResult::hasNullParameters() const
{
    return m_parameters.isNull();
}

QString ImportResult::errorString() const
{
    return m_errorString;
}

QSharedPointer<ImportResult> ImportResult::nullResult()
{
    return QSharedPointer<ImportResult>(new ImportResult());
}

QSharedPointer<ImportResult> ImportResult::error(QString errorString)
{
    auto result = new ImportResult();
    result->m_errorString = errorString;
    return QSharedPointer<ImportResult>(result);
}

QSharedPointer<ImportResult> ImportResult::result(QSharedPointer<BitContainer> container, Parameters parameters)
{
    return QSharedPointer<ImportResult>((new ImportResult())->setContainer(container)->setParameters(parameters));
}
