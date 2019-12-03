// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php

#include "themelight.h"

void ThemeLight::init() 
{
    font_family = "'Helvetica Neue'";
    
    status_bar_background = "#f4f6f9";
    widgets_background = "#ffffff";
    menu_background = "#e3e9ef";
    input_background = "#FFFFFF";
    frame_background = "#e3e9ef";
    selected_item_background = "#79a6d2";
    text_color = "#5c5f76";
    alt_text_color = "#ffffff";
    alternate_background = "#d8d8d8";
    tab_background = "#d5d5db";
    selected_tab_background = "#aaaabe";
    push_button_text_color = "#5c5f76";
    push_button_border_color = "#65676b";
    push_button_background = "#e8e5e5"; 
    selected_menu_item_background = "#6b6b6b";
    tree_item_alternate_background = "#538cc6";
    progress_bar_background = "#3dc28b";
    tableview_text_color = "#565656";
    scrollbar_handle_color = "#ffffff";
    disabled_text_color = "#757596";

    table_header_background = title_background;
    
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
    fontBiggerIco = ":/icons/fontbigger_light";
    fontSmallerIco = ":/icons/fontsmaller_light";
    hdEnabledIco = ":/icons/hd_enabled";
    hdDisabledIco = ":/icons/hd_disabled";
    warningIco = ":/icons/warning";
    deepVaultLogoIco = ":/icons/deepVaultLogoColor";
    
    spinnerPath = ":/movies/spinner-%1";

    Theme::init();
}
