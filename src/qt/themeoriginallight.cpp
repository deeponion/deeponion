//
//

#include "themeoriginallight.h"


ThemeOriginalLight::ThemeOriginalLight() 
	: Theme()
{
	init();
	init2();
}

void ThemeOriginalLight::init() 
{
    title_background = "#486EBA";
    status_bar_background = "#f4f6f9";
    widgets_background = "#D8D8D8";
    menu_background = "#bdc9db";
    input_background = "#FFFFFF"; 
    frame_background = "#FFFFFF";
    font_family = "'Helvetica Neue'";
    selected_item_background = "#79a6d2";
    QString text_color = "#2B2B37";
    alternate_background = "#D8D8D8";
    tab_background = "#D8D8D8"; 
    selected_tab_background = "#D8D8D8"; 
    secondary_label_color = "#486EBA"; 
    push_button_text_color = "#2A2937";
    push_button_border_color = "#65676b";
    push_button_background = "#e8e5e5";
    selected_menu_item_background = "#6b6b6b";
    tree_item_alternate_background = "#538cc6";
    progress_bar_background = "#3dc28b";
    tableview_text_color = "#565656";
    scrollbar_handle_color = " rgba(255, 255, 255, 0%)";
    disabled_text_color = "#757596";

    mainMenuOverviewNormalBtnIco = ":/icons/overview";
    mainMenuSendcoinsNormalBtnIco = ":/icons/send";
    mainMenuReceiveCoinsNormalBtnIco = ":/icons/receiving_addresses";
    mainMenuTransactionsNormalBtnIco = ":/icons/history";
    mainMenuAddressBookNormalBtnIco = ":/icons/address-book";
    mainMenuMessagesNormalBtnIco = ":/icons/messaging";
    mainMenuExportNormalBtnIco = ":/icons/export";
	mainMenuUnlockWalletNormalBtnIco = ":/icons/lock_open";
	mainMenuLockWalletNormalBtnIco = ":/icons/lock_closed";
    mainMenuDeepVaultNormalBtnIco = ":/icons/deepvault";
    
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
    aboutImg = ":/images/about_light";
    fontBiggerIco = ":/icons/fontbigger_light";
    fontSmallerIco = ":/icons/fontsmaller_light";
    hdEnabledIco = ":/icons/hd_enabled";
    hdDisabledIco = ":/icons/hd_disabled";
    warningIco = ":/icons/warning";
    deepVaultLogoIco = ":/icons/deepVaultLogoColor";
    deepOnionLogo = ":/icons/DeepOnionLogo";
}
