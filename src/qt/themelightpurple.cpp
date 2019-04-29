// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php

#include "themelightpurple.h"

ThemeLightPurple::ThemeLightPurple()
{
	init();
}

void ThemeLightPurple::init() 
{
    title_background = "#7d50cf";

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
    
    aboutImg = ":/images/about_light_purple";
    deepOnionLogo = ":/icons/DeepOnionLogoPurple";
    
    ThemeLight::init();
}
