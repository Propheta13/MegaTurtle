#include "msettingsdialog.h"
#include "ui_msettingsdialog.h"

MSettingsDialog::MSettingsDialog(MSettings::settings_t *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MSettingsDialog)
{
    ui->setupUi(this);
    m_settings = settings;
    ui->horizontalSlider->setValue(m_settings->tail_resolution);
}

MSettingsDialog::~MSettingsDialog()
{
    delete ui;
}

void MSettingsDialog::accept()
{
    m_settings->tail_resolution = (ui->horizontalSlider->value()/4)*4;
    QDialog::accept();
}

void MSettingsDialog::reject()
{
    QDialog::reject();
}
