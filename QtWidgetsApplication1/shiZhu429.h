#pragma once
#include "cav_l1.h"

#define tx_channel  3  // TX channel number,0 - 33
#define rx_channel  3  // RX channel number,0 - 33 
#define DEVID (CAV_PRODUCT_PMCA429 | CAV_DEVID_BOARDNUM_01 | CAV_DEVID_CHANNELTYPE_A429)


using namespace std;

class cav429
{
public:
	cav429();
	~cav429();
	void init();

};



