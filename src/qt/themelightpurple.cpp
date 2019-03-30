// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php

#include "themelightpurple.h"

ThemeLightPurple::ThemeLightPurple() 
	: Theme()
{
	init();
	init2();
}

void ThemeLightPurple::init() 
{
    title_background = "#7d50cf";
    status_bar_background = "#f4f6f9";
    widgets_background = "#D8D8D8";
    menu_background = "#bdc9db";
    input_background = "#bdc9db"; 
    frame_background = "#ffffff";
    font_family = "'Helvetica Neue'";
    selected_item_background = "#79a6d2";
    text_color = "#2B2B37";
    alternate_background = "#FFFFFF"; 
    tab_background = "#474757"; 
    selected_tab_background = "#7272a3"; 
    secondary_label_color = "#898994"; 
    push_button_text_color = "#2A2937";
    push_button_border_color = "#65676b";
    push_button_background = "#e8e5e5"; 
    selected_menu_item_background = "#6b6b6b";
    tree_item_alternate_background = "#538cc6";
    progress_bar_background = "#3dc28b";
    tableview_text_color = "#565656";
    scrollbar_handle_color = " rgba(255, 255, 255, 0%)";
    disabled_text_color = "#757596";
    table_header_background = "#b49be4";
    
    mainMenuOverviewNormalBtnIco = ":/icons/purple/overview";
    mainMenuSendcoinsNormalBtnIco = ":/icons/purple/send";
    mainMenuReceiveCoinsNormalBtnIco = ":/icons/purple/receiving_addresses";
    mainMenuTransactionsNormalBtnIco = ":/icons/purple/history";
    mainMenuAddressBookNormalBtnIco = ":/icons/purple/address-book";
    mainMenuMessagesNormalBtnIco = ":/icons/purple/messaging";
    mainMenuExportNormalBtnIco = ":/icons/purple/export";
    mainMenuUnlockWalletNormalBtnIco = ":/icons/purple/lock_open";
    mainMenuLockWalletNormalBtnIco = ":/icons/purple/lock_closed";
    mainMenuDeepVaultNormalBtnIco = ":/icons/purple/deepvault";
    
    mainMenuOverviewSelectedBtnIco = ":/icons/OverviewS";
    mainMenuSendcoinsSelectedBtnIco = ":/icons/SendCoinsS";
    mainMenuReceiveCoinsSelectedBtnIco = ":/icons/ReceiveCoinsS";
    mainMenuTransactionsSelectedBtnIco = ":/icons/TransactionsS";
    mainMenuAddressBookSelectedBtnIco = ":/icons/AddressBookS";
    mainMenuMessagesSelectedBtnIco = ":/icons/MessagesS";
    mainMenuExportSelectedBtnIco = ":/icons/ExportUS";
    mainMenuUnlockWalletSelectedBtnIco = ":/icons/lock_open";
    mainMenuLockWalletSelectedBtnIco = ":/icons/lock_closed";
    mainMenuDeepVaultSelectedBtnIco = ":/icons/deepvault_s";

    mainMenuExportDeactivatedBtnIco = ":/icons/export_disabled";
    informationIco = ":/icons/information-blue";
    aboutImg = ":/images/about_light_purple";
    fontBiggerIco = ":/icons/fontbigger_light";
    fontSmallerIco = ":/icons/fontsmaller_light";
    hdEnabledIco = ":/icons/hd_enabled";
    hdDisabledIco = ":/icons/hd_disabled";
    warningIco = ":/icons/warning";
    deepVaultLogoIco = ":/icons/deepVaultLogoColor";
    deepOnionLogo = ":/icons/DeepOnionLogoPurple";
}
