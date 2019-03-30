// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php


#ifndef DEEPONION_THEME_THEME_H
#define DEEPONION_THEME_THEME_H

#include <QString>


class Theme {
	
public:
	
    const QString getStyleSheet() const;

	const QString getCentralWidgetStyle() const;
    const QString getQFrameGeneralStyle() const;
    const QString getQFrameSecondaryMenuGeneralStyle() const;
    const QString getQLabelGeneralStyle() const;
    const QString getQTableGeneralStyle() const;
    const QString getQListHeaderGeneralStyle() const;
    const QString getQLineEdit() const;
    const QString getQLineEditPassword() const;
    const QString getIconTextButtonStyle() const;
    const QString getInformationIco() const;
    const QString getInformationBtnStyle() const;
    const QString getQComboboxTransactionsFilteringStyle() const;
    const QString getQComboboxDateRangeStyle() const;
    const QString getQComboboxValueStyle() const;
    const QString getQToolBtnStyle() const;
    const QString getQPushBtnStyle() const;
    const QString getAboutImg() const;
    const QString getFontBiggerIco() const;
    const QString getFontSmallerIco() const;
    const QString getQTreeWidget() const;
    const QString getHDEnabledIco() const;
    const QString getHDDisabledIco() const;
    const QString getWarningIco() const;

    const QString getMainMenuOverviewNormalBtnIco() const;
    const QString getMainMenuSendcoinsNormalBtnIco() const;
    const QString getMainMenuReceiveCoinsNormalBtnIco() const;
    const QString getMainMenuTransactionsNormalBtnIco() const;
    const QString getMainMenuAddressBookNormalBtnIco() const;
    const QString getMainMenuMessagesNormalBtnIco() const;
    const QString getMainMenuExportNormalBtnIco() const;
    const QString getMainMenuUnlockWalletNormalBtnIco() const;
    const QString getMainMenuLockWalletNormalBtnIco() const;
    const QString getMainMenuDeepVaultNormalBtnIco() const;

    const QString getMainMenuOverviewSelectedBtnIco() const;
    const QString getMainMenuSendcoinsSelectedBtnIco() const;
    const QString getMainMenuReceiveCoinsSelectedBtnIco() const;
    const QString getMainMenuTransactionsSelectedBtnIco() const;
    const QString getMainMenuAddressBookSelectedBtnIco() const;
    const QString getMainMenuMessagesSelectedBtnIco() const;
    const QString getMainMenuExportSelectedBtnIco() const;
    const QString getMainMenuUnlockWalletSelectedBtnIco() const;
    const QString getMainMenuLockWalletSelectedBtnIco() const;
    const QString getMainMenuDeepVaultSelectedBtnIco() const;  
    const QString getMainMenuExportDeactivatedBtnIco() const;
	const QString getStatusBarBackgroundColor() const;
    const QString getProgressBarStyle() const;
    const QString getDeepVaultLogoIco() const;
	const QString getDeepVaultLogoBtnStyle() const;
	const QString getRadioTextStyle() const;
    const QString getPayAmountStyle() const;

    const QString getMainHeaderStyle() const;
    const QString getMenuHeaderStyle() const;
    const QString getSubSectionTitleStyle() const;
    const QString getRoundedButtonStyle() const;
	const QString getDeepOnionLogo() const;


protected:
	void init2();
	
    QString themeStyleSheet;
    QString centralWidgetStyle;

    QString mainMenuOverviewNormalBtnIco;
    QString mainMenuSendcoinsNormalBtnIco;
    QString mainMenuReceiveCoinsNormalBtnIco;
    QString mainMenuTransactionsNormalBtnIco;
    QString mainMenuAddressBookNormalBtnIco;
    QString mainMenuMessagesNormalBtnIco;
    QString mainMenuExportNormalBtnIco;
    QString mainMenuUnlockWalletNormalBtnIco;
    QString mainMenuLockWalletNormalBtnIco;
    QString mainMenuDeepVaultNormalBtnIco;
    
    QString mainMenuOverviewSelectedBtnIco;
    QString mainMenuSendcoinsSelectedBtnIco;
    QString mainMenuReceiveCoinsSelectedBtnIco;
    QString mainMenuTransactionsSelectedBtnIco;
    QString mainMenuAddressBookSelectedBtnIco;
    QString mainMenuMessagesSelectedBtnIco;
    QString mainMenuExportSelectedBtnIco;
    QString mainMenuUnlockWalletSelectedBtnIco;
    QString mainMenuLockWalletSelectedBtnIco;
    QString mainMenuDeepVaultSelectedBtnIco;
    
    QString mainMenuExportDeactivatedBtnIco;

    QString qFrameGeneralStyle;
    QString qFrameSecondaryMenuGeneralStyle;
    QString qLabelGeneralStyle;
    QString qTableGeneralStyle;
    QString qListHeaderGeneralStyle;
    QString qLineEdit;
    QString qLineEditPassword;
    QString iconTextButtonStyle;
    QString informationIco;
    QString informationBtnStyle;
    QString qComboboxTransactionsFilteringStyle;
    QString qComboboxDateRangeStyle;
    QString qComboboxValueStyle;
    QString qToolBtnStyle;
    QString qPushBtnStyle;
    QString aboutImg;
    QString fontBiggerIco;
    QString fontSmallerIco;
    QString hdEnabledIco;
    QString hdDisabledIco;
    QString warningIco;
    QString qTreeWidget;
	QString statusBarBackgroundColor;
    QString progressBarStyle;
    QString deepVaultLogoIco;
	QString deepVaultLogoBtnStyle;
	QString radioTextStyle;
    QString payAmountStyle;
	QString mainHeaderStyle;
    QString menuHeaderStyle;
    QString subSectionTitleStyle;
    QString roundedButtonStyle;
    QString deepOnionLogo;
    
	QString title_background;
    QString status_bar_background;
    QString widgets_background;
    QString menu_background;
    QString input_background;
    QString frame_background;
    QString font_family;
    QString selected_item_background;
    QString text_color;
    QString alternate_background;
    QString tab_background;
    QString selected_tab_background;
    QString secondary_label_color;
    QString push_button_text_color;
    QString push_button_border_color;
    QString push_button_background;
    QString selected_menu_item_background;
    QString tree_item_alternate_background;
    QString progress_bar_background;
    QString tableview_text_color;
    QString scrollbar_handle_color;
    QString disabled_text_color;
};


#endif //DEEPONION_THEME_THEME_H
