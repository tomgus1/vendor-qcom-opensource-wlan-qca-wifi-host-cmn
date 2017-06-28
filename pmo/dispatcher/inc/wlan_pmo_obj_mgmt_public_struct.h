/*
* Copyright (c) 2017 The Linux Foundation. All rights reserved.
*
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all
* copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
* WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
* AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
* DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
* PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
* TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
* PERFORMANCE OF THIS SOFTWARE.
*/
 /**
  * DOC: Declare various struct, macros which are used for object mgmt in pmo.
  *
  * Note: This file shall not contain public API's prototype/declarations.
  *
  */


#ifndef _WLAN_PMO_OBJ_MGMT_PUBLIC_STRUCT_H_
#define _WLAN_PMO_OBJ_MGMT_PUBLIC_STRUCT_H_

#include "wlan_pmo_common_public_struct.h"
#include "wlan_pmo_arp_public_struct.h"
#include "wlan_pmo_ns_public_struct.h"
#include "wlan_pmo_gtk_public_struct.h"
#include "wlan_pmo_wow_public_struct.h"
#include "wlan_pmo_mc_addr_filtering_public_struct.h"

/**
 * typedef for vdev notifying the vdev pause bitmap new value to mlme
 */
typedef void (*pmo_notify_pause_bitmap)(
			uint8_t vdev_id, uint16_t value);

/**
 * typedef for getting vdev pause bitmap
 */
typedef  uint16_t(*pmo_get_pause_bitmap)(uint8_t vdev_id);

/**
 * typedef to know is deviec is in power save mode
 */
typedef  bool (*pmo_is_device_in_low_pwr_mode)(uint8_t vdev_id);

/**
 * struct pmo_psoc_priv_obj - psoc related data require for pmo
 * @psoc_cfg: place holder for psoc configuration
 * @wow: wow configuration
 * @dp_hdl: psoc data path handle
 * @htc_hdl: htc layer handle
 * @hif_hdl: hif layer handle
 * @txrx_hdl: txrx pdev handle
 * @pause_bitmap_notifier: registered callback to update pause bitmap value
 * @pmo_get_pause_bitmap: registered callback to get pause bitmap value
 * @lock: spin lock for pmo psoc
 */
struct pmo_psoc_priv_obj {
	struct pmo_psoc_cfg psoc_cfg;
	struct pmo_wow wow;
	void *dp_hdl;
	void *htc_hdl;
	void *hif_hdl;
	void *txrx_hdl;
	pmo_notify_pause_bitmap pause_bitmap_notifier;
	pmo_get_pause_bitmap get_pause_bitmap;
	pmo_is_device_in_low_pwr_mode is_device_in_low_pwr_mode;
	qdf_spinlock_t lock;
};

/**
 * struct wlan_pmo_ctx -offload mgr context
 * @psoc_context:     psoc context
 * @pmo_suspend_handler: suspend handler table for all componenets
 * @pmo_suspend_handler_arg: suspend handler argument sfor all componenets
 * @pmo_resume_handler: resume handler table for all componenets
 * @pmo_resume_handler_arg: resume handler argument for all componenets
 * @lock: lock for global pmo ctx
 */
struct wlan_pmo_ctx {
	pmo_psoc_suspend_handler
		pmo_suspend_handler[WLAN_UMAC_MAX_COMPONENTS];
	void *pmo_suspend_handler_arg[WLAN_UMAC_MAX_COMPONENTS];
	pmo_psoc_resume_handler
		pmo_resume_handler[WLAN_UMAC_MAX_COMPONENTS];
	void *pmo_resume_handler_arg[WLAN_UMAC_MAX_COMPONENTS];
	qdf_spinlock_t lock;
};

/**
 * struct pmo_vdev_priv_obj -vdev specific user configuration required for pmo
 * @pmo_psoc_ctx: pmo psoc ctx
 * @vdev_arp_req: place holder for arp request for vdev
 * @vdev_ns_req: place holder for ns request for vdev
 * @vdev_mc_list_req: place holder for mc addr list for vdev
 * @addr_filter_pattern: addr filter pattern for vdev
 * @vdev_gtk_params: place holder for gtk request for vdev
 * @gtk_err_enable: gtk error is enabled or not
 * @vdev_bpf_req: place holder for apf/bpf for vdev
 * @vdev_pkt_filter: place holder for vdev packet filter
 * @ptrn_match_enable: true when pattern match is enabled else false
 * @num_wow_default_patterns: number of wow default patterns for vdev
 * @num_wow_user_patterns: number of user wow patterns for vdev
 * @nlo_in_progress: true when pno/nlo in progress else false
 * @nlo_match_received: true when nlo match recevied from fwr else false
 * @extscan_in_progress: true when extscan in progress else false
 * @p2plo_in_progress: true when p2plo_in_progress in progress else false
 * @dtim_period: dtim period for vdev
 * @beacon_interval: vdev beacon interval
 * @alt_modulated_dtim_enabled:dynamic modulated dtim enabled
 * @dtim_policy: tells vdev beacon dtim policy
 * @vdev_dp_hdl: vdev data path handle
 * @pmo_vdev_lock: spin lock for pmo vdev priv ctx
 */
struct pmo_vdev_priv_obj {
	struct pmo_psoc_priv_obj *pmo_psoc_ctx;
	struct pmo_arp_offload_params vdev_arp_req;
	struct pmo_ns_offload_params vdev_ns_req;
	struct pmo_mc_addr_list vdev_mc_list_req;
	uint8_t addr_filter_pattern;
	struct pmo_gtk_req vdev_gtk_req;
	struct pmo_gtk_rsp_req vdev_gtk_rsp_req;
	qdf_atomic_t gtk_err_enable;
	bool ptrn_match_enable;
	uint8_t num_wow_default_patterns;
	uint8_t num_wow_user_patterns;
	bool nlo_in_progress;
	bool nlo_match_received;
	bool extscan_in_progress;
	bool p2plo_in_progress;
	uint8_t dtim_period;
	uint8_t beacon_interval;
	bool alt_modulated_dtim_enable;
	uint32_t dtim_policy;
	void *vdev_dp_hdl;
	qdf_spinlock_t pmo_vdev_lock;
};

/*
 * typedef for pld auto suspend callback during runtime suspend
 */
typedef
int (*pmo_pld_auto_suspend_cb)(void);

/*
 * typedef for pld auto resume callback during runtime resume
 */
typedef
int (*pmo_pld_auto_resume_cb)(void);
#endif /* end  of _WLAN_PMO_OBJ_MGMT_PUBLIC_STRUCT_H_ */