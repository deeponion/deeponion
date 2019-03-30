// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php


#include "theme.h"

void Theme::init2() {

    themeStyleSheet = "QComboBox {color: #FFFFFF; background-color: " + push_button_text_color + "; height: 26px;} \
        QComboBox:hover {background-color: " + frame_background + "; color: " + push_button_text_color + ";  height: 26px;} \
        QWidget {color: " + push_button_text_color + "; background-color: " + menu_background + ";} \
        QMenu {color: " + text_color + "; background-color: " + menu_background + "; border-color: " + menu_background + ";} \
    	QMenu::item:selected {background-color: " + selected_menu_item_background + ";}\
   		QMainWindow {background-color: " + frame_background + "; border:none;font-family:" + font_family + ";} \
   		QHeaderView::section {color: " + text_color + "; background-color: " + tab_background + "; } \
    	QPlainTextEdit {color: " + text_color + "; background-color: " + input_background + "; selection-background-color: " + selected_item_background + "; font-size: 13px; font-family: " + font_family + ";} \
        QPlainTextEdit:ContextMenu {height: 200px;}\
        QTextEdit {color: " + text_color + "; background-color: " + input_background + "; selection-background-color: " + selected_item_background + "; font-size: 13px; font-family: " + font_family + ";} \
        QLineEdit {border: 1px solid gray; background-color: " + input_background + "; color: " + text_color + "; selection-background-color: " + selected_item_background + "; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px;} \
        QLineEdit:hover {border: 1px solid gray; background-color: " + input_background + "; color: " + text_color + "; selection-background-color: " + selected_item_background + "; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px;} \
        QLineEdit:ContextMenu {height: 200px;}\
        QTabWidget {color: " + text_color + "; background-color: " + frame_background + ";} \
        QTabWidget::pane {color: " + text_color + "; background-color: " + frame_background + "; border: 1px solid " + input_background + ";} \
        QTabBar::tab {color: " + text_color + "; background-color: " + tab_background + "; border: 1px solid " + frame_background + "; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
        QTabBar::tab:selected, QTabBar::tab:hover {color:" + text_color + "; background-color: " + selected_tab_background + "; border: 1px solid " + frame_background + "; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
        QDialog {color: " + text_color + "; background-color: " + frame_background + ";} \
        QCheckBox {color: " + text_color + "; background-color: " + frame_background + ";} \
        QLabel {color: " + text_color + "; background-color: " + frame_background + "; font-family:" + font_family + ";} \
        QLabel#labelTotalText {color: " + secondary_label_color + ";}\
        QLabel#labelTotal {color: " + text_color + ";}\
        QLabel#labelBalanceText {color: " + secondary_label_color + ";}\
        QLabel#labelBalance {color: " + text_color + ";}\
        QLabel#labelStakeText {color: " + secondary_label_color + ";}\
        QLabel#labelStake {color: " + text_color + ";}\
        QLabel#labelUnconfirmedText {color: " + secondary_label_color + ";}\
        QLabel#labelUnconfirmed {color: " + text_color + ";}\
        QLabel#labelImmatureText {color: " + secondary_label_color + ";}\
        QLabel#labelImmature {color: " + text_color + ";}\
        QToolBar {color: " + text_color + "; background-color: " + frame_background + "; border: 0px;} \
        QToolBar QToolButton {width: 180px; border:0; height:30px; padding-left: 10px; text-align:left; color: " + text_color + "; background-color: " + frame_background + "} \
        QToolBar QToolButton:pressed {border:0; height:30px; padding-left: 10px; text-align:left; color: " + text_color + "; background-color: " + title_background + "} \
        QToolBar QToolButton:checked {border:0; height:30px; padding-left: 10px; text-align:left; color: " + text_color + "; background-color: " + title_background + "} \
        QTreeView { color: " + text_color + "; background-color:" + frame_background + "; alternate-background-color: " + tree_item_alternate_background + ";} \
        QTreeView::item {color: " + text_color + "; background-color: " + frame_background + "; border: 1px solid " + frame_background + ";} \
        QTreeView::item:hover {color: " + text_color + "; background-color: " + selected_item_background + "; border: 1px solid " + frame_background + ";} \
        QToolButton {color: " + text_color + "; background-color: " + frame_background + "; padding: 3px; border: none;} \
        QDialogButtonBox {color: " + text_color + "; background-color: " + frame_background + "; padding: 3px;} \
        QMenuBar {background-color: " + menu_background + ";} \
        QToolTip {color: " + text_color + "; border: 0px; background-color: " + menu_background + "; opacity: 225;} \
        QMenuBar::item {color: " + text_color + "; background-color: " + menu_background + " ;} \
        QMenuBar::item:selected {color: " + text_color + "; font-weight: bold; background-color: " + menu_background + ";}\
        QPushButton {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + input_background + "; color: " + push_button_text_color + "; padding: 8px}\
        QPushButton:pressed {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
        QPushButton:hover {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
	    QPushButton:disabled {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + disabled_text_color + ";}\
        QStatusBar::item { border: 0px}\
        QProgressBar::horizontal { text-align: middle;}\
        QProgressBar::chunk { background-color:" + progress_bar_background + ";}\
        QTableView {color: " + tableview_text_color + "; alternate-background-color: " + alternate_background + "; background-color: " + widgets_background + ";}\
        QScrollBar:vertical {border: 1px solid " + input_background + "; background: " + input_background + "; width: 24px; margin: 5px 5px 5px 5px;}\
        QScrollBar::handle:vertical {border-radius: 4px; background: " + scrollbar_handle_color + "; min-height: 25px; max-width: 12px; }\
        QScrollBar::add-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}\
        QScrollBar::sub-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}\
        QScrollBar:horizontal {border: 1px solid " + input_background + "; background: " + input_background + "; width: 24px; margin: 5px 5px 5px 5px;}\
        QScrollBar::handle:horizontal {border-radius: 4px; background: " + scrollbar_handle_color + "; min-height: 25px; max-width: 12px; }\
        QScrollBar::add-line:horizontal { background: " + alternate_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}\
        QScrollBar::sub-line:horizontal { background: " + alternate_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";

	centralWidgetStyle = "background: " + input_background + "";

	qFrameGeneralStyle = "background-color: " + frame_background + ";";
	qFrameSecondaryMenuGeneralStyle = "background-color: " + push_button_background + "; padding: 8px;";
	qLabelGeneralStyle = "color: " + text_color + "";
	qTableGeneralStyle = "QTableView {color: " + tableview_text_color + "; alternate-background-color: " + alternate_background + "; background-color: " + widgets_background + ";} \
		QScrollBar:vertical {border: 1px solid " + input_background + "; background: " + input_background + "; width: 24px; margin: 5px 5px 5px 5px;} \
		QScrollBar::handle:vertical {border-radius: 4px; background: " + scrollbar_handle_color + "; min-height: 25px; max-width: 12px; } \
		QScrollBar::add-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
		QScrollBar::sub-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";
	qListHeaderGeneralStyle = "QHeaderView::section {background-color: " + table_header_background + "; color: " + text_color + "; border: none; \
		font-size: 12px; font-family: Helvetica Neue; \
		padding-left: 8px; padding-right: 8px; \
		padding-top: 8px; padding-bottom: 8px;}";
	qLineEdit = "QLineEdit {background-color: " + input_background + "; color: " + text_color + "; padding-left: 5px; font-family: " + font_family + "; height: 32px;}  QLineEdit:ContextMenu {height: 200px;}";
	qLineEditPassword = "QLineEdit {background-color: " + input_background + "; color: " + text_color + "; padding-left: 5px; font-family: " + font_family + "; height: 32px;}  QLineEdit:ContextMenu {height: 200px;}";
	payAmountStyle = "background-color: " + input_background + "; color: " + text_color + "; padding-left: 5px; font-family: " + font_family + "; height: 32px;";
	iconTextButtonStyle = "QPushButton, QPushButton:hover {color: " + text_color + "; border: none; background-color: rgba(255, 255, 255, 0);}";
	informationBtnStyle = "background-color: " + frame_background + "; border: none";
	qComboboxTransactionsFilteringStyle = "QComboBox { background-color: " + frame_background + "; color: " + text_color + "; font-size: 14px; font-family: " + font_family + ";\
		padding-left: 8px; padding-top: 4px; padding-bottom: 4px; border: none; }\
		QComboBox::drop-down {border: none; background: " + title_background + "; width: 30px;}\
		QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
	qComboboxDateRangeStyle = "background-color: " + frame_background + "; color: " + text_color + "; font-size: 14px; font-family: " + font_family + ";\
		border: none; QComboBox::drop-down {border: none}";
	qComboboxValueStyle = "QComboBox { background-color: " + frame_background + "; color: " + text_color + "; font-size: 14px; font-family: " + font_family + "; border: none; }\
        QComboBox::drop-down {border: none;  background: " + title_background + "; width: 30px; height: 30px;}\
        QComboBox::down-arrow { width: 10px; height: 10px; image: url(:/icons/arrow_down_white);}\
	    QAbstractItemView {min-height: 70px; min-width: 100px;}";
	qToolBtnStyle = "{color: " + text_color + "; background-color: " + frame_background + "; padding: 3px; border: none;}";
	qPushBtnStyle = "QPushButton {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + input_background + "; color: " + push_button_text_color + "; padding: 8px}\
		QPushButton:pressed {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
		QPushButton:hover {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
		QPushButton:disabled {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + disabled_text_color + ";}";
	qTreeWidget = "QTreeView { color: " + text_color + "; background-color:" + frame_background + "; alternate-background-color: " + tree_item_alternate_background + ";} \
		QTreeView::item {color: " + text_color + "; background-color: " + frame_background + "; border: 1px solid " + frame_background + ";} \
		QTreeView::item:hover {color: " + text_color + "; background-color: " + selected_item_background + "; border: 1px solid " + frame_background + ";}";
	statusBarBackgroundColor = "background-color: " + status_bar_background + "; color: " + text_color + "";
	progressBarStyle = "color: " + progress_bar_background + "; padding-left: 10px;  background-color: " + status_bar_background + ";";
    deepVaultLogoBtnStyle = "background-color: " + frame_background + "; border: none";
	radioTextStyle = "color: " + text_color;
    mainHeaderStyle = "background-color: " + title_background + "; color: white; padding-right: 10px; font-size: 24px; font-weight: bold";
    menuHeaderStyle = "QToolBar {background: " + title_background + "; border: 0px;} \
        QToolBar QToolButton {background: " + title_background + "; padding-left: 10px; padding-top: 10px; text-align:left;}";
    subSectionTitleStyle = "padding-left: 10px; background-color: " + title_background + ";";
    roundedButtonStyle = "background-color: " + title_background + ";color: white;border-radius:14px;border-width:0px; margin-left: 8px;";
}


const QString Theme::getStyleSheet() const {
    return themeStyleSheet;
}

const QString Theme::getCentralWidgetStyle() const {
    return centralWidgetStyle;
}

const QString Theme::getQFrameGeneralStyle() const {
    return qFrameGeneralStyle;
}

const QString Theme::getQFrameSecondaryMenuGeneralStyle() const {
    return qFrameSecondaryMenuGeneralStyle;
}

const QString Theme::getQLabelGeneralStyle() const {
    return qLabelGeneralStyle;
}

const QString Theme::getQTableGeneralStyle() const {
    return qTableGeneralStyle;
}

const QString Theme::getQListHeaderGeneralStyle() const {
    return qListHeaderGeneralStyle;
}

const QString Theme::getQLineEdit() const {
    return qLineEdit;
}

const QString Theme::getQLineEditPassword() const {
    return qLineEditPassword;
}

const QString Theme::getIconTextButtonStyle() const {
    return iconTextButtonStyle;
}

const QString Theme::getInformationIco() const {
    return informationIco;
}

const QString Theme::getInformationBtnStyle() const {
    return informationBtnStyle;
}

const QString Theme::getQComboboxTransactionsFilteringStyle() const {
    return qComboboxTransactionsFilteringStyle;
}

const QString Theme::getQComboboxDateRangeStyle() const {
    return qComboboxDateRangeStyle;
}

const QString Theme::getQComboboxValueStyle() const {
    return qComboboxValueStyle;
}

const QString Theme::getQToolBtnStyle() const {
    return qToolBtnStyle;
}

const QString Theme::getQPushBtnStyle() const {
    return qPushBtnStyle;
}

const QString Theme::getAboutImg() const {
    return aboutImg;
}

const QString Theme::getFontBiggerIco() const {
    return fontBiggerIco;
}

const QString Theme::getFontSmallerIco() const {
    return fontSmallerIco;
}

const QString Theme::getHDEnabledIco() const {
    return hdEnabledIco;
}

const QString Theme::getHDDisabledIco() const {
    return hdDisabledIco;
}

const QString Theme::getWarningIco() const {
    return warningIco;
}

const QString Theme::getQTreeWidget() const {
    return qTreeWidget;
}

const QString Theme::getMainMenuOverviewNormalBtnIco() const {
    return mainMenuOverviewNormalBtnIco;
}

const QString Theme::getMainMenuSendcoinsNormalBtnIco() const {
    return mainMenuSendcoinsNormalBtnIco;
}

const QString Theme::getMainMenuReceiveCoinsNormalBtnIco() const {
    return mainMenuReceiveCoinsNormalBtnIco;
}

const QString Theme::getMainMenuTransactionsNormalBtnIco() const {
    return mainMenuTransactionsNormalBtnIco;
}

const QString Theme::getMainMenuAddressBookNormalBtnIco() const {
    return mainMenuAddressBookNormalBtnIco;
}

const QString Theme::getMainMenuMessagesNormalBtnIco() const {
    return mainMenuMessagesNormalBtnIco;
}

const QString Theme::getMainMenuExportNormalBtnIco() const {
    return mainMenuExportNormalBtnIco;
}

const QString Theme::getMainMenuUnlockWalletNormalBtnIco() const {
    return mainMenuUnlockWalletNormalBtnIco;
}

const QString Theme::getMainMenuLockWalletNormalBtnIco() const {
    return mainMenuLockWalletNormalBtnIco;
}

const QString Theme::getMainMenuDeepVaultNormalBtnIco() const {
    return mainMenuDeepVaultNormalBtnIco;
}


const QString Theme::getMainMenuOverviewSelectedBtnIco() const {
    return mainMenuOverviewSelectedBtnIco;
}

const QString Theme::getMainMenuSendcoinsSelectedBtnIco() const {
    return mainMenuSendcoinsSelectedBtnIco;
}

const QString Theme::getMainMenuReceiveCoinsSelectedBtnIco() const {
    return mainMenuReceiveCoinsSelectedBtnIco;
}

const QString Theme::getMainMenuTransactionsSelectedBtnIco() const {
    return mainMenuTransactionsSelectedBtnIco;
}

const QString Theme::getMainMenuAddressBookSelectedBtnIco() const {
    return mainMenuAddressBookSelectedBtnIco;
}

const QString Theme::getMainMenuMessagesSelectedBtnIco() const {
    return mainMenuMessagesSelectedBtnIco;
}

const QString Theme::getMainMenuExportSelectedBtnIco() const {
    return mainMenuExportSelectedBtnIco;
}

const QString Theme::getMainMenuUnlockWalletSelectedBtnIco() const {
    return mainMenuUnlockWalletSelectedBtnIco;
}

const QString Theme::getMainMenuLockWalletSelectedBtnIco() const {
    return mainMenuLockWalletSelectedBtnIco;
}

const QString Theme::getMainMenuDeepVaultSelectedBtnIco() const {
    return mainMenuDeepVaultSelectedBtnIco;
}

const QString Theme::getMainMenuExportDeactivatedBtnIco() const {
    return mainMenuExportDeactivatedBtnIco;
}


const QString Theme::getStatusBarBackgroundColor() const {
    return statusBarBackgroundColor;
}

const QString Theme::getProgressBarStyle() const {
    return progressBarStyle;
}

const QString Theme::getDeepVaultLogoIco() const {
    return deepVaultLogoIco;
}

const QString Theme::getDeepVaultLogoBtnStyle() const {
    return deepVaultLogoBtnStyle;
}

const QString Theme::getRadioTextStyle() const {
    return radioTextStyle;
}

const QString Theme::getPayAmountStyle() const {
    return payAmountStyle;
}

const QString Theme::getMainHeaderStyle() const {
    return mainHeaderStyle;
}

const QString Theme::getMenuHeaderStyle() const {
    return menuHeaderStyle;
}

const QString Theme::getSubSectionTitleStyle() const {
    return subSectionTitleStyle;
}

const QString Theme::getRoundedButtonStyle() const {
    return roundedButtonStyle;
}

const QString Theme::getDeepOnionLogo()const {
    return deepOnionLogo;
}

