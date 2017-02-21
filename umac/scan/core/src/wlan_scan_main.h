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

/*
 * DOC: contains scan init/deinit public api
 */

#ifndef _WLAN_SCAN_MAIN_API_H_
#define _WLAN_SCAN_MAIN_API_H_

#include <qdf_atomic.h>
#include <wlan_objmgr_psoc_obj.h>
#include <wlan_objmgr_pdev_obj.h>
#include <wlan_objmgr_vdev_obj.h>
#include <wlan_scan_public_structs.h>
#include "wlan_scan_cache_db.h"

#define scm_log(level, args...) \
		QDF_TRACE(QDF_MODULE_ID_SCAN, level, ## args)
#define scm_logfl(level, format, args...) \
		scm_log(level, FL(format), ## args)
#define scm_alert(format, args...) \
		scm_logfl(QDF_TRACE_LEVEL_FATAL, format, ## args)
#define scm_err(format, args...) \
		scm_logfl(QDF_TRACE_LEVEL_ERROR, format, ## args)
#define scm_warn(format, args...) \
		scm_logfl(QDF_TRACE_LEVEL_WARN, format, ## args)
#define scm_notice(format, args...) \
		scm_logfl(QDF_TRACE_LEVEL_INFO, format, ## args)
#define scm_info(format, args...) \
		scm_logfl(QDF_TRACE_LEVEL_INFO_HIGH, format, ## args)
#define scm_debug(format, args...) \
		scm_logfl(QDF_TRACE_LEVEL_DEBUG, format, ## args)

#define MAX_SCAN_EVENT_HANDLERS_PER_PDEV   100
#define WLAN_MAX_MODULE_NAME    40
#define WLAN_MAX_REQUESTORS     200
#define WLAN_SCAN_ID_MASK 0x00000FFF
#define WLAN_HOST_SCAN_REQ_ID_PREFIX 0x0000A000
#define WLAN_SCAN_REQUESTER_ID_PREFIX 0x0000A000

#ifdef CONFIG_MCL
#define SCAN_ACTIVE_DWELL_TIME 20
#define SCAN_PASSIVE_DWELL_TIME 100
#define SCAN_MAX_REST_TIME 20
#define SCAN_MIN_REST_TIME 0
#define SCAN_BURST_DURATION 20
#define SCAN_CONC_ACTIVE_DWELL_TIME 20
#define SCAN_CONC_PASSIVE_DWELL_TIME 100
#define SCAN_CONC_IDLE_TIME 25
#define SCAN_CONC_MAX_REST_TIME 20
#define SCAN_CONC_MIN_REST_TIME 10
#define SCAN_REPEAT_PROBE_TIME 11
#define SCAN_PROBE_SPACING_TIME 0
#define SCAN_PROBE_DELAY 0
#define SCAN_MAX_SCAN_TIME 30000
#define SCAN_NUM_PROBES 3
#define SCAN_NETWORK_IDLE_TIMEOUT 0
#else
#define SCAN_ACTIVE_DWELL_TIME 105
#define SCAN_PASSIVE_DWELL_TIME 300
#define SCAN_MAX_REST_TIME 0
#define SCAN_MIN_REST_TIME 50
#define SCAN_BURST_DURATION 0
#define SCAN_CONC_ACTIVE_DWELL_TIME 0
#define SCAN_CONC_PASSIVE_DWELL_TIME 0
#define SCAN_CONC_IDLE_TIME 0
#define SCAN_CONC_MAX_REST_TIME 0
#define SCAN_CONC_MIN_REST_TIME 0
#define SCAN_REPEAT_PROBE_TIME 50
#define SCAN_PROBE_SPACING_TIME 0
#define SCAN_PROBE_DELAY 0
#define SCAN_MAX_SCAN_TIME 50000
#define SCAN_NUM_PROBES 0
#define SCAN_NETWORK_IDLE_TIMEOUT 200
#endif

#define SCAN_TIMEOUT_GRACE_PERIOD 10
/* scan age time in millisec */
#define SCAN_CACHE_AGING_TIME (300*1000)
#define SCAN_MAX_BSS_PDEV 100
#define SCAN_MAX_NUM_SCAN_ALLOWED 8
#define SCAN_PRIORITY SCAN_PRIORITY_LOW

/**
 * struct cb_handler - defines scan event handler
 * call back function and arguments
 * @func: handler function pointer
 * @arg: argument to handler function
 */
struct cb_handler {
	scan_event_handler func;
	void *arg;
};

/**
 * struct pdev_scan_ev_handler - pdev scan event handlers
 * @cb_handler: array of registered scan handlers
 */
struct pdev_scan_ev_handler {
	uint32_t handler_cnt;
	struct cb_handler cb_handlers[MAX_SCAN_EVENT_HANDLERS_PER_PDEV];
};

/**
 * struct global_scan_ev_handlers - per pdev registered scan event handlers
 * @pdev_scan_ev_handler: per pdev registered scan event handlers
 */
struct global_scan_ev_handlers {
	struct pdev_scan_ev_handler pdev_ev_handlers[WLAN_UMAC_MAX_PDEVS];
};

/**
 * struct scan_requester_info - defines scan requester id
 * and event handler mapping
 * @requester:   requester ID allocated
 * @module:      module name of requester
 * @ev_handler:  event handlerto be invoked
 */
struct scan_requester_info {
	wlan_scan_requester requester;
	uint8_t module[WLAN_MAX_MODULE_NAME];
	struct cb_handler ev_handler;
};

/**
 * struct pdev_scan_info - defines per pdev scan info
 * @last_scan_time: time of last scan start on this pdev
 */

struct pdev_scan_info {
	qdf_time_t last_scan_time;
};

/**
 * struct scan_default_params - default scan parameters to be used
 * @active_dwell: default active dwell time
 * @passive_dwell:default passive dwell time
 * @max_rest_time: default max rest time
 * @min_rest_time: default min rest time
 * @idle_time: default idle time
 * @conc_active_dwell: default concurrent active dwell time
 * @conc_passive_dwell: default concurrent passive dwell time
 * @conc_max_rest_time: default concurrent max rest time
 * @conc_min_rest_time: default concurrent min rest time
 * @conc_idle_time: default concurrent idle time
 * @repeat_probe_time: default repeat probe time
 * @probe_spacing_time: default probe spacing time
 * @probe_delay: default probe delay
 * @burst_duration: default burst duration
 * @max_scan_time: default max scan time
 * @num_probes: default maximum number of probes to sent
 * @cache_aging_time: default scan cache aging time
 * @max_bss_per_pdev: maximum number of bss entries to be maintained per pdev
 * @max_num_scan_allowed: maximum number of parallel scan allowed per psoc
 * @scan_priority: default scan priority
 * @scan_f_passive: passively scan all channels including active channels
 * @scan_f_bcast_probe: add wild card ssid prbreq even if ssid_list is specified
 * @scan_f_cck_rates: add cck rates to rates/xrates ie in prb req
 * @scan_f_ofdm_rates: add ofdm rates to rates/xrates ie in prb req
 * @scan_f_chan_stat_evnt: enable indication of chan load and noise floor
 * @scan_f_filter_prb_req: filter Probe request frames
 * @scan_f_bypass_dfs_chn: when set, do not scan DFS channels
 * @scan_f_continue_on_err:continue scan even if few certain erros have occurred
 * @scan_f_offchan_mgmt_tx: allow mgmt transmission during off channel scan
 * @scan_f_offchan_data_tx: allow data transmission during off channel scan
 * @scan_f_promisc_mode: scan with promiscuous mode
 * @scan_f_capture_phy_err: enable capture ppdu with phy errrors
 * @scan_f_strict_passive_pch: do passive scan on passive channels
 * @scan_f_half_rate: enable HALF (10MHz) rate support
 * @scan_f_quarter_rate: set Quarter (5MHz) rate support
 * @scan_f_force_active_dfs_chn: allow to send probe req on DFS channel
 * @scan_f_add_tpc_ie_in_probe: add TPC ie in probe req frame
 * @scan_f_add_ds_ie_in_probe: add DS ie in probe req frame
 * @scan_f_add_spoofed_mac_in_probe: use random mac address for TA in probe
 * @scan_f_add_rand_seq_in_probe: use random sequence number in probe
 * @scan_f_en_ie_whitelist_in_probe: enable ie whitelist in probe
 * @scan_flags: variable to read and set scan_f_* flags in one shot
 *              can be used to dump all scan_f_* flags for debug
 * @scan_ev_started: notify scan started event
 * @scan_ev_completed: notify scan completed event
 * @scan_ev_bss_chan: notify bss chan event
 * @scan_ev_foreign_chan: notify foreign chan event
 * @scan_ev_dequeued: notify scan request dequed event
 * @scan_ev_preempted: notify scan preempted event
 * @scan_ev_start_failed: notify scan start failed event
 * @scan_ev_restarted: notify scan restarted event
 * @scan_ev_foreign_chn_exit: notify foreign chan exit event
 * @scan_ev_invalid: notify invalid scan request event
 * @scan_ev_gpio_timeout: notify gpio timeout event
 * @scan_ev_suspended: notify scan suspend event
 * @scan_ev_resumed: notify scan resumed event
 * @scan_events: variable to read and set scan_ev_* flags in one shot
 *               can be used to dump all scan_ev_* flags for debug
 */
struct scan_default_params {
	uint32_t active_dwell;
	uint32_t passive_dwell;
	uint32_t max_rest_time;
	uint32_t min_rest_time;
	uint32_t idle_time;
	uint32_t conc_active_dwell;
	uint32_t conc_passive_dwell;
	uint32_t conc_max_rest_time;
	uint32_t conc_min_rest_time;
	uint32_t conc_idle_time;
	uint32_t repeat_probe_time;
	uint32_t probe_spacing_time;
	uint32_t probe_delay;
	uint32_t burst_duration;
	uint32_t max_scan_time;
	uint32_t num_probes;
	uint32_t scan_cache_aging_time;
	uint16_t max_bss_per_pdev;
	uint8_t max_num_scan_allowed;
	enum scan_priority scan_priority;
	union {
		struct {
			uint32_t scan_f_passive:1,
				scan_f_bcast_probe:1,
				scan_f_cck_rates:1,
				scan_f_ofdm_rates:1,
				scan_f_chan_stat_evnt:1,
				scan_f_filter_prb_req:1,
				scan_f_bypass_dfs_chn:1,
				scan_f_continue_on_err:1,
				scan_f_offchan_mgmt_tx:1,
				scan_f_offchan_data_tx:1,
				scan_f_promisc_mode:1,
				scan_f_capture_phy_err:1,
				scan_f_strict_passive_pch:1,
				scan_f_half_rate:1,
				scan_f_quarter_rate:1,
				scan_f_force_active_dfs_chn:1,
				scan_f_add_tpc_ie_in_probe:1,
				scan_f_add_ds_ie_in_probe:1,
				scan_f_add_spoofed_mac_in_probe:1,
				scan_f_add_rand_seq_in_probe:1,
				scan_f_en_ie_whitelist_in_probe:1,
				scan_f_forced:1,
				scan_f_2ghz:1,
				scan_f_5ghz:1,
				scan_f_80mhz:1;
		};
		uint32_t scan_flags;
	};
	union {
		struct {
			uint32_t scan_ev_started:1,
				scan_ev_completed:1,
				scan_ev_bss_chan:1,
				scan_ev_foreign_chan:1,
				scan_ev_dequeued:1,
				scan_ev_preempted:1,
				scan_ev_start_failed:1,
				scan_ev_restarted:1,
				scan_ev_foreign_chn_exit:1,
				scan_ev_invalid:1,
				scan_ev_gpio_timeout:1,
				scan_ev_suspended:1,
				scan_ev_resumed:1;
		};
		uint32_t scan_events;
	};
};

/**
 * struct scan_cb - nif/sif function callbacks
 * @inform_beacon: cb to indicate frame to OS
 * @update_beacon: cb to indicate frame to MLME
 */
struct scan_cb {
	update_beacon_cb inform_beacon;
	update_beacon_cb update_beacon;
	/* Define nif/sif function callbacks here */
};

/**
 * struct wlan_scan_obj - scan object definition
 * @scan_db:    scan cache data base
 * @lock:       spin lock
 * @scan_def:   default scan parameters
 * @cb:         nif/sif function callbacks
 * @requesters: requester allocation pool
 * @scan_ids:   last allocated scan id
 * @global_evhandlers:  registered scan event handlers
 */
struct wlan_scan_obj {
	qdf_spinlock_t lock;
	qdf_atomic_t scan_ids;
	struct scan_dbs scan_db[WLAN_UMAC_MAX_PDEVS];
	struct scan_default_params scan_def;
	struct scan_cb cb;
	struct scan_requester_info requesters[WLAN_MAX_REQUESTORS];
	struct global_scan_ev_handlers global_evhandlers;
	struct pdev_scan_info pdev_info[WLAN_UMAC_MAX_PDEVS];
};

/**
 * wlan_vdev_get_scan_obj() - private API to get scan object from vdev
 * @psoc: vdev object
 *
 * Return: scan object
 */
static inline struct wlan_scan_obj *
wlan_vdev_get_scan_obj(struct wlan_objmgr_vdev *vdev)
{
	struct wlan_objmgr_psoc *psoc =
		wlan_pdev_get_psoc(wlan_vdev_get_pdev(vdev));

	return (struct wlan_scan_obj *)
		wlan_objmgr_psoc_get_comp_private_obj(psoc,
				WLAN_UMAC_COMP_SCAN);
}

/**
 * wlan_psoc_get_scan_obj() - private API to get scan object from psoc
 * @psoc: psoc object
 *
 * Return: scan object
 */
static inline struct wlan_scan_obj *
wlan_psoc_get_scan_obj(struct wlan_objmgr_psoc *psoc)
{
	return (struct wlan_scan_obj *)
		wlan_objmgr_psoc_get_comp_private_obj(psoc,
				WLAN_UMAC_COMP_SCAN);
}

/**
 * wlan_scan_vdev_get_pdev_id)() - private API to get pdev id from vdev object
 * @vdev: vdev object
 *
 * Return: parent pdev id
 */
static inline uint8_t
wlan_scan_vdev_get_pdev_id(struct wlan_objmgr_vdev *vdev)
{
	struct wlan_objmgr_pdev *pdev = wlan_vdev_get_pdev(vdev);

	return wlan_objmgr_pdev_get_pdev_id(pdev);
}

/**
 * wlan_vdev_get_pdev_scan_ev_handlers() - private API to get
 * pdev scan event handlers
 * @vdev: vdev object
 *
 * Return: pdev_scan_ev_handler object
 */
static inline struct pdev_scan_ev_handler*
wlan_vdev_get_pdev_scan_ev_handlers(struct wlan_objmgr_vdev *vdev)
{
	uint8_t pdevid = wlan_scan_vdev_get_pdev_id(vdev);
	struct wlan_scan_obj *scan = wlan_vdev_get_scan_obj(vdev);
	struct pdev_scan_ev_handler *pdev_ev_handler =
		&scan->global_evhandlers.pdev_ev_handlers[pdevid];

	return pdev_ev_handler;
}

/**
 * wlan_vdev_get_def_scan_params() - private API to get scan defaults
 * @psoc: vdev object
 *
 * Return: scan defaults
 */
static inline struct scan_default_params*
wlan_vdev_get_def_scan_params(struct wlan_objmgr_vdev *vdev)
{
	struct wlan_scan_obj *scan = wlan_vdev_get_scan_obj(vdev);

	return &scan->scan_def;
}

/**
 * wlan_scan_psoc_created_notification() - scan psoc create handler
 * @psoc: psoc object
 * @arg_list: Argument list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS wlan_scan_psoc_created_notification(struct wlan_objmgr_psoc *psoc,
	void *arg_list);

/**
 * wlan_scan_psoc_deleted_notification() - scan psoc delete handler
 * @psoc: psoc object
 * @arg_list: Argument list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS wlan_scan_psoc_destroyed_notification(struct wlan_objmgr_psoc *psoc,
	void *arg_list);
#endif