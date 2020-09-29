// Copyright (c) 2011-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/editaddressdialog.h>
#include <qt/forms/ui_editaddressdialog.h>

#include <qt/addresstablemodel.h>
#include <qt/guiutil.h>

#include <QDataWidgetMapper>
#include <QMessageBox>

#include <wallet/wallet.h>

extern OutputType g_address_type;

EditAddressDialog::EditAddressDialog(Mode _mode, QWidget* parent) : QDialog(parent),
                                                                    ui(new Ui::EditAddressDialog),
                                                                    mapper(0),
                                                                    mode(_mode),
                                                                    model(0)
{
    ui->setupUi(this);

    GUIUtil::setupAddressWidget(ui->addressEdit, this);

    switch (mode) {
    case NewReceivingAddress:
        setWindowTitle(tr("New receiving address"));
        ui->addressEdit->setEnabled(false);
        ui->addressEdit->setVisible(false);
        ui->label_2->setVisible(false);
        ui->addressType->setVisible(true);
        {
            if (g_address_type == OUTPUT_TYPE_P2SH_SEGWIT) {
                ui->bech32RB->setEnabled(true);
                ui->stealthRB->setEnabled(true);
                ui->segwitRB->setEnabled(true);
                ui->legacyRB->setEnabled(true);
            } else {
                ui->bech32RB->setDisabled(true);
                ui->bech32RB->setStyleSheet("color: gray");
                ui->bech32RB->setToolTip("This type of address will be enabled with the activation of segwit.");
                ui->stealthRB->setEnabled(true);
                ui->segwitRB->setStyleSheet("color: gray");
                ui->segwitRB->setToolTip("This type of address will be enabled with the activation of segwit.");
                ui->segwitRB->setDisabled(true);
                ui->legacyRB->setEnabled(true);
            }
        }
        //Check default addresstype
        getDefaultAddressButton()->setChecked(true);
        break;
    case NewSendingAddress:
        setWindowTitle(tr("New sending address"));
        ui->addressType->hide();
        break;
    case EditReceivingAddress:
        setWindowTitle(tr("Edit receiving address"));
        ui->addressEdit->setEnabled(false);
        ui->addressType->hide();
        break;
    case EditSendingAddress:
        setWindowTitle(tr("Edit sending address"));
        ui->addressType->hide();
        break;
    }

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

EditAddressDialog::~EditAddressDialog()
{
    delete ui;
}

void EditAddressDialog::setModel(AddressTableModel* _model)
{
    this->model = _model;
    if (!_model)
        return;

    mapper->setModel(_model);
    mapper->addMapping(ui->labelEdit, AddressTableModel::Label);
    mapper->addMapping(ui->addressEdit, AddressTableModel::Address);
}

void EditAddressDialog::loadRow(int row)
{
    mapper->setCurrentIndex(row);
}

bool EditAddressDialog::saveCurrentRow()
{
    if (!model)
        return false;

    switch (mode) {
    case NewReceivingAddress:
    case NewSendingAddress:
        OutputType type;
        if (ui->legacyRB->isChecked())
            type = OUTPUT_TYPE_LEGACY;
        else if (ui->stealthRB->isChecked())
            type = OUTPUT_TYPE_STEALTH;
        else if (ui->bech32RB->isChecked())
            type = OUTPUT_TYPE_BECH32;
        else if (ui->segwitRB->isChecked())
            type = OUTPUT_TYPE_P2SH_SEGWIT;

        address = model->addRow(
            mode == NewSendingAddress ? AddressTableModel::Send : AddressTableModel::Receive,
            ui->labelEdit->text(),
            ui->addressEdit->text(),
            type);
        break;
    case EditReceivingAddress:
    case EditSendingAddress:
        if (mapper->submit()) {
            address = ui->addressEdit->text();
        }
        break;
    }
    return !address.isEmpty();
}

void EditAddressDialog::accept()
{
    if (!model)
        return;

    if (!saveCurrentRow()) {
        switch (model->getEditStatus()) {
        case AddressTableModel::OK:
            // Failed with unknown reason. Just reject.
            break;
        case AddressTableModel::NO_CHANGES:
            // No changes were made during edit operation. Just reject.
            break;
        case AddressTableModel::INVALID_ADDRESS:
            QMessageBox::warning(this, windowTitle(),
                tr("The entered address \"%1\" is not a valid DeepOnion address.").arg(ui->addressEdit->text()),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case AddressTableModel::DUPLICATE_ADDRESS:
            QMessageBox::warning(this, windowTitle(),
                tr("The entered address \"%1\" is already in the address book.").arg(ui->addressEdit->text()),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case AddressTableModel::WALLET_UNLOCK_FAILURE:
            QMessageBox::critical(this, windowTitle(),
                tr("Could not unlock wallet."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case AddressTableModel::KEY_GENERATION_FAILURE:
            QMessageBox::critical(this, windowTitle(),
                tr("New key generation failed."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        }
        return;
    }
    QDialog::accept();
}

QString EditAddressDialog::getAddress() const
{
    return address;
}

void EditAddressDialog::setAddress(const QString& _address)
{
    this->address = _address;
    ui->addressEdit->setText(_address);
}

QRadioButton* EditAddressDialog::getDefaultAddressButton()
{
    switch (g_address_type) {
    case OUTPUT_TYPE_LEGACY:
        addDefaultInfoText(ui->legacyRB);
        return ui->legacyRB;
    case OUTPUT_TYPE_P2SH_SEGWIT:
        addDefaultInfoText(ui->segwitRB);
        return ui->segwitRB;
    case OUTPUT_TYPE_BECH32:
        addDefaultInfoText(ui->bech32RB);
        return ui->bech32RB;
    case OUTPUT_TYPE_STEALTH:
        addDefaultInfoText(ui->stealthRB);
        return ui->stealthRB;
    }
}
