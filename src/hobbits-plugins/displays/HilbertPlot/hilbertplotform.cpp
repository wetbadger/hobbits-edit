#include "hilbertplotform.h"
#include "ui_hilbertplotform.h"

HilbertPlotForm::HilbertPlotForm(QSharedPointer<ParameterDelegate> delegate):
    ui(new Ui::HilbertPlotForm()),
    m_paramHelper(new ParameterHelper(delegate))
{
    ui->setupUi(this);
}

HilbertPlotForm::~HilbertPlotForm()
{
    delete ui;
}

QString HilbertPlotForm::title()
{
    return "Configure Hilbert Plot";
}

Parameters HilbertPlotForm::parameters()
{
    return m_paramHelper->getParametersFromUi();
}

bool HilbertPlotForm::setParameters(const Parameters &parameters)
{
    return m_paramHelper->applyParametersToUi(parameters);
}
