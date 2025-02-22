/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#ifndef NM_WFI_CFGOPERATIONS
#define NM_WFI_CFGOPERATIONS
#include "wilc_wfi_netdevice.h"

struct wilc *wilc_create_wiphy(struct device *dev);
void wilc_free_wiphy(struct net_device *net);
void wilc_deinit_host_int(struct net_device *net);
int wilc_init_host_int(struct net_device *net);
void wilc_wfi_monitor_rx(struct net_device *mon_dev, u8 *buff, u32 size);
void wilc_wfi_deinit_mon_interface(struct wilc *wl, bool rtnl_locked);
struct net_device *wilc_wfi_init_mon_interface(struct wilc *wl,
					       const char *name,
					       struct net_device *real_dev);
void wilc_mgmt_frame_register(struct wiphy *wiphy, struct wireless_dev *wdev,
			      u16 frame_type, bool reg);
void wilc_sysfs_init(struct wilc *wilc);
void wilc_sysfs_exit(void);
int wilc_cfg80211_init(struct wilc **wilc, struct device *dev, int io_type,
		       const struct wilc_hif_func *ops);
int wilc_get_vif_from_type(struct wilc *wl, int type);
struct wilc_vif *wilc_get_interface(struct wilc *wl);
void wlan_deinit_locks(struct wilc *wl);
#endif
