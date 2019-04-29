// Copyright (c) 2017-2019 The DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php


#include "themefancypurple.h"

ThemeFancyPurple::ThemeFancyPurple()
{
	init();
}

void ThemeFancyPurple::init()
{
    title_background = "#7d50cf";

	aboutImg = ":/images/about_dark_purple";
    deepOnionLogo = ":/icons/DeepOnionLogoPurple";
    
    ThemeDark::init();
}
