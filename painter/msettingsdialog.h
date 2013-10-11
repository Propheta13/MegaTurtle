#ifndef MSETTINGSDIALOG_H
#define MSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class MSettingsDialog;
}

namespace MSettings {
    typedef struct settings
    {
        quint32 tail_resolution;
    } settings_t;
}

class MSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MSettingsDialog(MSettings::settings_t *settings, QWidget *parent = 0);
    ~MSettingsDialog();
    
private:
    Ui::MSettingsDialog *ui;
    MSettings::settings_t *m_settings;

private slots:
    void accept();
    void reject();
};

#endif // MSETTINGSDIALOG_H
