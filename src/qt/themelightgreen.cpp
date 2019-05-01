// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php

#include "themelightgreen.h"

ThemeLightGreen::ThemeLightGreen()
{
	init();
}

void ThemeLightGreen::init() 
{
    title_background = "#61ac56";

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
    
    aboutImg = ":/images/about_light_green";
    deepOnionLogo = ":/icons/DeepOnionLogoGreen";
    
    ThemeLight::init();
}
