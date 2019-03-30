// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php

#include "themeoriginaldark.h"


ThemeOriginalDark::ThemeOriginalDark() 
	: Theme()
{
	init();
	init2();
}

void ThemeOriginalDark::init() 
{
	title_background = "#486EBA";
    status_bar_background = "#1A1A21";
    widgets_background = "#393848";
    menu_background = "#2A2937";
    input_background = "#2b2b37";
    frame_background = "#393947";
    font_family = "'Helvetica Neue'";
    selected_item_background = "#79a6d2";
    text_color = "#FFFFFF";
    alternate_background = "#474758";
    tab_background = "#474757";
    selected_tab_background = "#7272a3";
    secondary_label_color = "#898994";
    push_button_text_color = "#e9e8e8";
    push_button_border_color = "#65676b";
    push_button_background = "#22222b";
    selected_menu_item_background = "#1C1B15";
    tree_item_alternate_background = "#538cc6";
    progress_bar_background = "#3dc28b";
    tableview_text_color = "#D5D5D9";
    scrollbar_handle_color = "#C1C1C1";
    disabled_text_color = "#757596";
             
	mainMenuOverviewNormalBtnIco = ":/icons/OverviewS";
	mainMenuSendcoinsNormalBtnIco = ":/icons/SendCoinsS";
	mainMenuReceiveCoinsNormalBtnIco = ":/icons/ReceiveCoinsS";
	mainMenuTransactionsNormalBtnIco = ":/icons/TransactionsS";
	mainMenuAddressBookNormalBtnIco = ":/icons/AddressBookS";
	mainMenuMessagesNormalBtnIco = ":/icons/MessagesS";
	mainMenuExportNormalBtnIco = ":/icons/ExportUS";
	mainMenuUnlockWalletNormalBtnIco = ":/icons/lock_open_s";
	mainMenuLockWalletNormalBtnIco = ":/icons/lock_closed_s";
    mainMenuDeepVaultNormalBtnIco = ":/icons/deepvault_s";
            
   	mainMenuOverviewSelectedBtnIco = ":/icons/OverviewS";
   	mainMenuSendcoinsSelectedBtnIco = ":/icons/SendCoinsS";
   	mainMenuReceiveCoinsSelectedBtnIco = ":/icons/ReceiveCoinsS";
  	mainMenuTransactionsSelectedBtnIco = ":/icons/TransactionsS";
  	mainMenuAddressBookSelectedBtnIco = ":/icons/AddressBookS";
  	mainMenuMessagesSelectedBtnIco = ":/icons/MessagesS";
  	mainMenuExportSelectedBtnIco = ":/icons/ExportUS";
  	mainMenuUnlockWalletSelectedBtnIco = ":/icons/lock_open_s";
   	mainMenuLockWalletSelectedBtnIco = ":/icons/lock_closed_s";
    mainMenuDeepVaultSelectedBtnIco = ":/icons/deepvault_s";

	mainMenuExportDeactivatedBtnIco = ":/icons/export_disabled";
	informationIco = ":/icons/information";
	aboutImg = ":/images/about_dark";
	fontBiggerIco = ":/icons/fontbigger_dark";
	fontSmallerIco = ":/icons/fontsmaller_dark";
    hdEnabledIco = ":/icons/hd_enabled_white";
    hdDisabledIco = ":/icons/hd_disabled_white";
    warningIco = ":/icons/warning_white";
    deepVaultLogoIco = ":/icons/deepVaultLogoWhite";
	deepOnionLogo = ":/icons/DeepOnionLogo";
}
