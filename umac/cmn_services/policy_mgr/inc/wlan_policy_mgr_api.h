/*
 * Copyright (c) 2012-2017 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
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
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

#ifndef __WLAN_POLICY_MGR_API_H
#define __WLAN_POLICY_MGR_API_H

/**
 * DOC: wlan_policy_mgr_api.h
 *
 * Concurrenct Connection Management entity
 */

/* Include files */
#include "qdf_types.h"
#include "qdf_status.h"
#include "wlan_objmgr_psoc_obj.h"
#include "wlan_policy_mgr_public_struct.h"

typedef const enum policy_mgr_pcl_type
	pm_dbs_pcl_second_connection_table_type
	[PM_MAX_ONE_CONNECTION_MODE][PM_MAX_NUM_OF_MODE]
	[PM_MAX_CONC_PRIORITY_MODE];

typedef const enum policy_mgr_pcl_type
	pm_dbs_pcl_third_connection_table_type
	[PM_MAX_TWO_CONNECTION_MODE][PM_MAX_NUM_OF_MODE]
	[PM_MAX_CONC_PRIORITY_MODE];

typedef const enum policy_mgr_conc_next_action
	policy_mgr_next_action_two_connection_table_type
	[PM_MAX_ONE_CONNECTION_MODE][POLICY_MGR_MAX_BAND];

typedef const enum policy_mgr_conc_next_action
	policy_mgr_next_action_three_connection_table_type
	[PM_MAX_TWO_CONNECTION_MODE][POLICY_MGR_MAX_BAND];

/**
 * policy_mgr_set_concurrency_mode() - To set concurrency mode
 * @mode: adapter mode
 *
 * This routine is called to set the concurrency mode
 *
 * Return: NONE
 */
void policy_mgr_set_concurrency_mode(enum tQDF_ADAPTER_MODE mode);

/**
 * policy_mgr_clear_concurrency_mode() - To clear concurrency mode
 * @mode: adapter mode
 *
 * This routine is called to clear the concurrency mode
 *
 * Return: NONE
 */
void policy_mgr_clear_concurrency_mode(enum tQDF_ADAPTER_MODE mode);

/**
 * policy_mgr_get_connection_count() - provides the count of
 * current connections
 * @psoc: PSOC object information
 *
 * This function provides the count of current connections
 *
 * Return: connection count
 */
uint32_t policy_mgr_get_connection_count(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_get_concurrency_mode() - return concurrency mode
 *
 * This routine is used to retrieve concurrency mode
 *
 * Return: uint32_t value of concurrency mask
 */
uint32_t policy_mgr_get_concurrency_mode(void);

/**
 * policy_mgr_search_and_check_for_session_conc() - Checks if
 * concurrecy is allowed
 * @psoc: PSOC object information
 * @session_id: Session id
 * @roam_profile: Pointer to the roam profile
 *
 * Searches and gets the channel number from the scan results and checks if
 * concurrency is allowed for the given session ID
 *
 * Non zero channel number if concurrency is allowed, zero otherwise
 */
uint8_t policy_mgr_search_and_check_for_session_conc(
		struct wlan_objmgr_psoc *psoc,
		uint8_t session_id, void *roam_profile);

/**
 * policy_mgr_check_for_session_conc() - Check if concurrency is
 * allowed for a session
 * @psoc: PSOC object information
 * @session_id: Session ID
 * @channel: Channel number
 *
 * Checks if connection is allowed for a given session_id
 *
 * True if the concurrency is allowed, false otherwise
 */
bool policy_mgr_check_for_session_conc(
	struct wlan_objmgr_psoc *psoc, uint8_t session_id, uint8_t channel);

/**
 * policy_mgr_handle_conc_multiport() - to handle multiport concurrency
 * @session_id: Session ID
 * @channel: Channel number
 *
 * This routine will handle STA side concurrency when policy manager
 * is enabled.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_handle_conc_multiport(
	struct wlan_objmgr_psoc *psoc, uint8_t session_id, uint8_t channel);

#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
/**
 * policy_mgr_check_concurrent_intf_and_restart_sap() - Check
 * concurrent change intf
 * @psoc: PSOC object information
 *
 * Checks the concurrent change interface and restarts SAP
 * Return: None
 */
void policy_mgr_check_concurrent_intf_and_restart_sap(
	struct wlan_objmgr_psoc *psoc);
#else
static inline void policy_mgr_check_concurrent_intf_and_restart_sap(
						struct wlan_objmgr_psoc *psoc)
{

}
#endif /* FEATURE_WLAN_MCC_TO_SCC_SWITCH */

/**
 * policy_mgr_is_mcc_in_24G() - Function to check for MCC in 2.4GHz
 * @psoc: PSOC object information
 *
 * This function is used to check for MCC operation in 2.4GHz band.
 * STA, P2P and SAP adapters are only considered.
 *
 * Return: Non zero value if MCC is detected in 2.4GHz band
 *
 */
uint8_t policy_mgr_is_mcc_in_24G(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_set_mas() - Function to set MAS value to UMAC
 * @psoc: PSOC object information
 * @mas_value: 0-Disable, 1-Enable MAS
 *
 * This function passes down the value of MAS to UMAC
 *
 * Return: Configuration message posting status, SUCCESS or Fail
 *
 */
int32_t policy_mgr_set_mas(struct wlan_objmgr_psoc *psoc, uint8_t mas_value);

/**
 * policy_mgr_set_mcc_p2p_quota() - Function to set quota for P2P
 * @psoc: PSOC object information
 * @set_value:          Qouta value for the interface
 *
 * This function is used to set the quota for P2P cases
 *
 * Return: Configuration message posting status, SUCCESS or Fail
 *
 */
int policy_mgr_set_mcc_p2p_quota(struct wlan_objmgr_psoc *psoc,
		uint32_t set_value);

/**
 * policy_mgr_change_mcc_go_beacon_interval() - Change MCC beacon interval
 * @psoc: PSOC object information
 *
 * Updates the beacon parameters of the GO in MCC scenario
 *
 * Return: Success or Failure depending on the overall function behavior
 */
QDF_STATUS policy_mgr_change_mcc_go_beacon_interval(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_go_set_mcc_p2p_quota() - Function to set quota for P2P GO
 * @psoc: PSOC object information
 * @set_value:          Qouta value for the interface
 *
 * This function is used to set the quota for P2P GO cases
 *
 * Return: Configuration message posting status, SUCCESS or Fail
 *
 */
int policy_mgr_go_set_mcc_p2p_quota(struct wlan_objmgr_psoc *psoc,
		uint32_t set_value);

/**
 * policy_mgr_set_mcc_latency() - Set MCC latency
 * @psoc: PSOC object information
 * @set_value: Latency value
 *
 * Sets the MCC latency value during STA-P2P concurrency
 *
 * Return: None
 */
void policy_mgr_set_mcc_latency(struct wlan_objmgr_psoc *psoc, int set_value);
#if defined(FEATURE_WLAN_MCC_TO_SCC_SWITCH)
/**
 * policy_mgr_change_sap_channel_with_csa() - Move SAP channel using (E)CSA
 * @psoc: PSOC object information
 * @hdd_ap_ctx: AP context
 *
 * Invoke the callback function to change SAP channel using (E)CSA
 *
 * Return: None
 */
void policy_mgr_change_sap_channel_with_csa(struct wlan_objmgr_psoc *psoc);
#else
static inline void policy_mgr_change_sap_channel_with_csa(
		struct wlan_objmgr_psoc *psoc)
{

}
#endif

/**
 * policy_mgr_incr_active_session() - increments the number of active sessions
 * @psoc: PSOC object information
 * @mode:	Adapter mode
 * @session_id: session ID for the connection session
 *
 * This function increments the number of active sessions maintained per device
 * mode. In the case of STA/P2P CLI/IBSS upon connection indication it is
 * incremented; In the case of SAP/P2P GO upon bss start it is incremented
 *
 * Return: None
 */
void policy_mgr_incr_active_session(struct wlan_objmgr_psoc *psoc,
		enum tQDF_ADAPTER_MODE mode, uint8_t sessionId);

/**
 * policy_mgr_decr_active_session() - decrements the number of active sessions
 * @psoc: PSOC object information
 * @mode: Adapter mode
 * @session_id: session ID for the connection session
 *
 * This function decrements the number of active sessions maintained per device
 * mode. In the case of STA/P2P CLI/IBSS upon disconnection it is decremented
 * In the case of SAP/P2P GO upon bss stop it is decremented
 *
 * Return: None
 */
void policy_mgr_decr_active_session(struct wlan_objmgr_psoc *psoc,
		enum tQDF_ADAPTER_MODE mode, uint8_t sessionId);

/**
 * policy_mgr_decr_session_set_pcl() - Decrement session count and set PCL
 * @psoc: PSOC object information
 * @mode: Adapter mode
 * @session_id: Session id
 *
 * Decrements the active session count and sets the PCL if a STA connection
 * exists
 *
 * Return: None
 */
void policy_mgr_decr_session_set_pcl(struct wlan_objmgr_psoc *psoc,
		enum tQDF_ADAPTER_MODE mode, uint8_t session_id);

/**
 * policy_mgr_get_channel() - provide channel number of given mode and vdevid
 * @psoc: PSOC object information
 * @mode: given  mode
 * @vdev_id: pointer to vdev_id
 *
 * This API will provide channel number of matching mode and vdevid.
 * If vdev_id is NULL then it will match only mode
 * If vdev_id is not NULL the it will match both mode and vdev_id
 *
 * Return: channel number
 */
uint8_t policy_mgr_get_channel(struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_con_mode mode, uint32_t *vdev_id);

/**
 * policy_mgr_get_pcl() - provides the preferred channel list for
 * new connection
 * @psoc: PSOC object information
 * @mode:	Device mode
 * @pcl_channels: PCL channels
 * @len: lenght of the PCL
 * @pcl_weight: Weights of the PCL
 * @weight_len: Max length of the weights list
 *
 * This function provides the preferred channel list on which
 * policy manager wants the new connection to come up. Various
 * connection decision making entities will using this function
 * to query the PCL info
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_pcl(struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_con_mode mode,
		uint8_t *pcl_channels, uint32_t *len,
		uint8_t *pcl_weight, uint32_t weight_len);

/**
 * policy_mgr_update_with_safe_channel_list() - provides the safe
 * channel list
 * @pcl_channels: channel list
 * @len: length of the list
 * @weight_list: Weights of the PCL
 * @weight_len: Max length of the weights list
 *
 * This function provides the safe channel list from the list
 * provided after consulting the channel avoidance list
 *
 * Return: None
 */
void policy_mgr_update_with_safe_channel_list(uint8_t *pcl_channels,
		uint32_t *len, uint8_t *weight_list, uint32_t weight_len);

/**
 * policy_mgr_get_nondfs_preferred_channel() - to get non-dfs preferred channel
 *                                           for given mode
 * @psoc: PSOC object information
 * @mode: mode for which preferred non-dfs channel is requested
 * @for_existing_conn: flag to indicate if preferred channel is requested
 *                     for existing connection
 *
 * this routine will return non-dfs channel
 * 1) for getting non-dfs preferred channel, first we check if there are any
 *    other connection exist whose channel is non-dfs. if yes then return that
 *    channel so that we can accommodate upto 3 mode concurrency.
 * 2) if there no any other connection present then query concurrency module
 *    to give preferred channel list. once we get preferred channel list, loop
 *    through list to find first non-dfs channel from ascending order.
 *
 * Return: uint8_t non-dfs channel
 */
uint8_t policy_mgr_get_nondfs_preferred_channel(struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_con_mode mode, bool for_existing_conn);

/**
 * policy_mgr_is_any_nondfs_chnl_present() - Find any non-dfs
 * channel from conc table
 * @psoc: PSOC object information
 * @channel: pointer to channel which needs to be filled
 *
 * In-case if any connection is already present whose channel is none dfs then
 * return that channel
 *
 * Return: true up-on finding non-dfs channel else false
 */
bool policy_mgr_is_any_nondfs_chnl_present(struct wlan_objmgr_psoc *psoc,
		uint8_t *channel);

/**
 * policy_mgr_is_any_dfs_beaconing_session_present() - to find
 * if any DFS session
 * @psoc: PSOC object information
 * @channel: pointer to channel number that needs to filled
 *
 * If any beaconing session such as SAP or GO present and it is on DFS channel
 * then this function will return true
 *
 * Return: true if session is on DFS or false if session is on non-dfs channel
 */
bool policy_mgr_is_any_dfs_beaconing_session_present(
		struct wlan_objmgr_psoc *psoc, uint8_t *channel);

/**
 * policy_mgr_allow_concurrency() - Check for allowed concurrency
 * combination
 * @psoc: PSOC object information
 * @mode:	new connection mode
 * @channel: channel on which new connection is coming up
 * @bw: Bandwidth requested by the connection (optional)
 *
 * When a new connection is about to come up check if current
 * concurrency combination including the new connection is
 * allowed or not based on the HW capability
 *
 * Return: True/False
 */
bool policy_mgr_allow_concurrency(struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_con_mode mode,
		uint8_t channel, enum hw_mode_bandwidth bw);

/**
 * policy_mgr_get_first_connection_pcl_table_index() - provides the
 * row index to firstConnectionPclTable to get to the correct
 * pcl
 * @psoc: PSOC object information
 *
 * This function provides the row index to
 * firstConnectionPclTable. The index is the preference config.
 *
 * Return: table index
 */
enum policy_mgr_conc_priority_mode
	policy_mgr_get_first_connection_pcl_table_index(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_get_second_connection_pcl_table_index() - provides the
 * row index to secondConnectionPclTable to get to the correct
 * pcl
 * @psoc: PSOC object information
 *
 * This function provides the row index to
 * secondConnectionPclTable. The index is derived based on
 * current connection, band on which it is on & chain mask it is
 * using, as obtained from pm_conc_connection_list.
 *
 * Return: table index
 */
enum policy_mgr_one_connection_mode
	policy_mgr_get_second_connection_pcl_table_index(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_get_third_connection_pcl_table_index() - provides the
 * row index to thirdConnectionPclTable to get to the correct
 * pcl
 * @psoc: PSOC object information
 *
 * This function provides the row index to
 * thirdConnectionPclTable. The index is derived based on
 * current connection, band on which it is on & chain mask it is
 * using, as obtained from pm_conc_connection_list.
 *
 * Return: table index
 */
enum policy_mgr_two_connection_mode
	policy_mgr_get_third_connection_pcl_table_index(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_incr_connection_count() - adds the new connection to
 * the current connections list
 * @psoc: PSOC object information
 * @vdev_id: vdev id
 *
 *
 * This function adds the new connection to the current
 * connections list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_incr_connection_count(struct wlan_objmgr_psoc *psoc,
		uint32_t vdev_id);

/**
 * policy_mgr_update_connection_info() - updates the existing
 * connection in the current connections list
 * @psoc: PSOC object information
 * @vdev_id: vdev id
 *
 *
 * This function adds the new connection to the current
 * connections list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_update_connection_info(struct wlan_objmgr_psoc *psoc,
		uint32_t vdev_id);

/**
 * policy_mgr_decr_connection_count() - remove the old connection
 * from the current connections list
 * @psoc: PSOC object information
 * @vdev_id: vdev id of the old connection
 *
 *
 * This function removes the old connection from the current
 * connections list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_decr_connection_count(struct wlan_objmgr_psoc *psoc,
		uint32_t vdev_id);

/**
 * policy_mgr_current_connections_update() - initiates actions
 * needed on current connections once channel has been decided
 * for the new connection
 * @psoc: PSOC object information
 * @session_id: Session id
 * @channel: Channel on which new connection will be
 * @reason: Reason for which connection update is required
 *
 * This function initiates initiates actions
 * needed on current connections once channel has been decided
 * for the new connection. Notifies UMAC & FW as well
 *
 * Return: QDF_STATUS enum
 */
QDF_STATUS policy_mgr_current_connections_update(struct wlan_objmgr_psoc *psoc,
		uint32_t session_id, uint8_t channel,
		enum policy_mgr_conn_update_reason);

/**
 * policy_mgr_is_ibss_conn_exist() - to check if IBSS connection already present
 * @psoc: PSOC object information
 * @ibss_channel: pointer to ibss channel which needs to be filled
 *
 * this routine will check if IBSS connection already exist or no. If it
 * exist then this routine will return true and fill the ibss_channel value.
 *
 * Return: true if ibss connection exist else false
 */
bool policy_mgr_is_ibss_conn_exist(struct wlan_objmgr_psoc *psoc,
		uint8_t *ibss_channel);

/**
 * policy_mgr_get_conn_info() - get the current connections list
 * @len: lenght of the list
 *
 * This function returns a pointer to the current connections
 * list
 *
 * Return: pointer to connection list
 */
struct policy_mgr_conc_connection_info *policy_mgr_get_conn_info(
		uint32_t *len);
#ifdef MPC_UT_FRAMEWORK
/**
 * policy_mgr_incr_connection_count_utfw() - adds the new
 * connection to the current connections list
 * @psoc: PSOC object information
 * @vdev_id: vdev id
 * @tx_streams: number of transmit spatial streams
 * @rx_streams: number of receive spatial streams
 * @chain_mask: chain mask
 * @type: connection type
 * @sub_type: connection subtype
 * @channelid: channel number
 * @mac_id: mac id
 *
 * This function adds the new connection to the current
 * connections list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_incr_connection_count_utfw(struct wlan_objmgr_psoc *psoc,
		uint32_t vdev_id, uint32_t tx_streams, uint32_t rx_streams,
		uint32_t chain_mask, uint32_t type, uint32_t sub_type,
		uint32_t channelid, uint32_t mac_id);

/**
 * policy_mgr_update_connection_info_utfw() - updates the
 * existing connection in the current connections list
 * @psoc: PSOC object information
 * @vdev_id: vdev id
 * @tx_streams: number of transmit spatial streams
 * @rx_streams: number of receive spatial streams
 * @chain_mask: chain mask
 * @type: connection type
 * @sub_type: connection subtype
 * @channelid: channel number
 * @mac_id: mac id
 *
 * This function updates the connection to the current
 * connections list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_update_connection_info_utfw(struct wlan_objmgr_psoc *psoc,
		uint32_t vdev_id, uint32_t tx_streams, uint32_t rx_streams,
		uint32_t chain_mask, uint32_t type, uint32_t sub_type,
		uint32_t channelid, uint32_t mac_id);

/**
 * policy_mgr_decr_connection_count_utfw() - remove the old
 * connection from the current connections list
 * @psoc: PSOC object information
 * @del_all: delete all entries
 * @vdev_id: vdev id
 *
 * This function removes the old connection from the current
 * connections list
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_decr_connection_count_utfw(struct wlan_objmgr_psoc *psoc,
		uint32_t del_all, uint32_t vdev_id);

/**
 * policy_mgr_get_pcl_from_first_conn_table() - Get PCL for new
 * connection from first connection table
 * @type: Connection mode of type 'policy_mgr_con_mode'
 * @sys_pref: System preference
 *
 * Get the PCL for a new connection
 *
 * Return: PCL channels enum
 */
enum policy_mgr_pcl_type policy_mgr_get_pcl_from_first_conn_table(
		enum policy_mgr_con_mode type,
		enum policy_mgr_conc_priority_mode sys_pref);

/**
 * policy_mgr_get_pcl_from_second_conn_table() - Get PCL for new
 * connection from second connection table
 * @idx: index into first connection table
 * @type: Connection mode of type 'policy_mgr_con_mode'
 * @sys_pref: System preference
 * @dbs_capable: if HW DBS capable
 *
 * Get the PCL for a new connection
 *
 * Return: PCL channels enum
 */
enum policy_mgr_pcl_type policy_mgr_get_pcl_from_second_conn_table(
	enum policy_mgr_one_connection_mode idx, enum policy_mgr_con_mode type,
	enum policy_mgr_conc_priority_mode sys_pref, uint8_t dbs_capable);

/**
 * policy_mgr_get_pcl_from_third_conn_table() - Get PCL for new
 * connection from third connection table
 * @idx: index into second connection table
 * @type: Connection mode of type 'policy_mgr_con_mode'
 * @sys_pref: System preference
 * @dbs_capable: if HW DBS capable
 *
 * Get the PCL for a new connection
 *
 * Return: PCL channels enum
 */
enum policy_mgr_pcl_type policy_mgr_get_pcl_from_third_conn_table(
	enum policy_mgr_two_connection_mode idx, enum policy_mgr_con_mode type,
	enum policy_mgr_conc_priority_mode sys_pref, uint8_t dbs_capable);
#else
static inline QDF_STATUS policy_mgr_incr_connection_count_utfw(
		struct wlan_objmgr_psoc *psoc, uint32_t vdev_id,
		uint32_t tx_streams, uint32_t rx_streams,
		uint32_t chain_mask, uint32_t type, uint32_t sub_type,
		uint32_t channelid, uint32_t mac_id)
{
	return QDF_STATUS_SUCCESS;
}
static inline QDF_STATUS policy_mgr_update_connection_info_utfw(
		struct wlan_objmgr_psoc *psoc, uint32_t vdev_id,
		uint32_t tx_streams, uint32_t rx_streams,
		uint32_t chain_mask, uint32_t type, uint32_t sub_type,
		uint32_t channelid, uint32_t mac_id)
{
	return QDF_STATUS_SUCCESS;
}
static inline QDF_STATUS policy_mgr_decr_connection_count_utfw(
		struct wlan_objmgr_psoc *psoc, uint32_t del_all,
		uint32_t vdev_id)
{
	return QDF_STATUS_SUCCESS;
}
#endif

/**
 * policy_mgr_convert_device_mode_to_qdf_type() - provides the
 * type translation from HDD to policy manager type
 * @device_mode: Generic connection mode type
 *
 *
 * This function provides the type translation
 *
 * Return: policy_mgr_con_mode enum
 */
enum policy_mgr_con_mode policy_mgr_convert_device_mode_to_qdf_type(
		enum tQDF_ADAPTER_MODE device_mode);

/**
 * policy_mgr_pdev_set_hw_mode() - Set HW mode command to FW
 * @psoc: PSOC object information
 * @session_id: Session ID
 * @mac0_ss: MAC0 spatial stream configuration
 * @mac0_bw: MAC0 bandwidth configuration
 * @mac1_ss: MAC1 spatial stream configuration
 * @mac1_bw: MAC1 bandwidth configuration
 * @dbs: HW DBS capability
 * @dfs: HW Agile DFS capability
 * @sbs: HW SBS capability
 * @reason: Reason for connection update
 *
 * Sends the set hw mode request to FW
 *
 * e.g.: To configure 2x2_80
 *       mac0_ss = HW_MODE_SS_2x2, mac0_bw = HW_MODE_80_MHZ
 *       mac1_ss = HW_MODE_SS_0x0, mac1_bw = HW_MODE_BW_NONE
 *       dbs = HW_MODE_DBS_NONE, dfs = HW_MODE_AGILE_DFS_NONE,
 *       sbs = HW_MODE_SBS_NONE
 * e.g.: To configure 1x1_80_1x1_40 (DBS)
 *       mac0_ss = HW_MODE_SS_1x1, mac0_bw = HW_MODE_80_MHZ
 *       mac1_ss = HW_MODE_SS_1x1, mac1_bw = HW_MODE_40_MHZ
 *       dbs = HW_MODE_DBS, dfs = HW_MODE_AGILE_DFS_NONE,
 *       sbs = HW_MODE_SBS_NONE
 * e.g.: To configure 1x1_80_1x1_40 (Agile DFS)
 *       mac0_ss = HW_MODE_SS_1x1, mac0_bw = HW_MODE_80_MHZ
 *       mac1_ss = HW_MODE_SS_1x1, mac1_bw = HW_MODE_40_MHZ
 *       dbs = HW_MODE_DBS, dfs = HW_MODE_AGILE_DFS,
 *       sbs = HW_MODE_SBS_NONE
 *
 * Return: Success if the message made it down to the next layer
 */
QDF_STATUS policy_mgr_pdev_set_hw_mode(struct wlan_objmgr_psoc *psoc,
		uint32_t session_id,
		enum hw_mode_ss_config mac0_ss,
		enum hw_mode_bandwidth mac0_bw,
		enum hw_mode_ss_config mac1_ss,
		enum hw_mode_bandwidth mac1_bw,
		enum hw_mode_dbs_capab dbs,
		enum hw_mode_agile_dfs_capab dfs,
		enum hw_mode_sbs_capab sbs,
		enum policy_mgr_conn_update_reason reason);

/**
 * policy_mgr_nss_update_cback() - callback invoked by other
 * component to provide nss update request status
 * @psoc: PSOC object information
 * @tx_status: tx completion status for updated beacon with new
 *		nss value
 * @vdev_id: vdev id for the specific connection
 * @next_action: next action to happen at policy mgr after
 *		beacon update
 * @reason: Reason for nss update
 *
 * This function is the callback registered with SME at nss
 * update request time
 *
 * Return: None
 */
typedef void (*policy_mgr_nss_update_cback)(struct wlan_objmgr_psoc *psoc,
		uint8_t tx_status,
		uint8_t vdev_id,
		uint8_t next_action,
		enum policy_mgr_conn_update_reason reason);

/**
 * struct policy_mgr_sme_cbacks - SME Callbacks to be invoked
 * from policy manager
 * @sme_get_valid_channels: Get valid channel list
 * @sme_get_nss_for_vdev: Get the allowed nss value for the vdev
 * @sme_soc_set_dual_mac_config: Set the dual MAC scan & FW
 *                             config
 * @sme_pdev_set_hw_mode: Set the new HW mode to FW
 * @sme_pdev_set_pcl: Set new PCL to FW
 * @sme_nss_update_request: Update NSS value to FW
 */
struct policy_mgr_sme_cbacks {
	QDF_STATUS (*sme_get_valid_channels)(uint8_t *chan_list,
		uint32_t *list_len);
	void (*sme_get_nss_for_vdev)(enum tQDF_ADAPTER_MODE,
		uint8_t *nss_2g, uint8_t *nss_5g);
	QDF_STATUS (*sme_soc_set_dual_mac_config)(
		struct policy_mgr_dual_mac_config msg);
	QDF_STATUS (*sme_pdev_set_hw_mode)(struct policy_mgr_hw_mode msg);
	QDF_STATUS (*sme_pdev_set_pcl)(struct policy_mgr_pcl_list msg);
	QDF_STATUS (*sme_nss_update_request)(uint32_t vdev_id,
		uint8_t  new_nss, policy_mgr_nss_update_cback cback,
		uint8_t next_action, struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_conn_update_reason reason);
};

/**
 * struct policy_mgr_tdls_cbacks - TDLS Callbacks to be invoked
 * from policy manager
 * @set_tdls_ct_mode: Set the tdls connection tracker mode
 * @check_is_tdls_allowed: check if tdls allowed or not
 */
struct policy_mgr_tdls_cbacks {
	void (*set_tdls_ct_mode)(struct wlan_objmgr_psoc *psoc);
	bool (*check_is_tdls_allowed)(enum tQDF_ADAPTER_MODE device_mode);
};

/**
 * struct policy_mgr_cdp_cbacks - CDP Callbacks to be invoked
 * from policy manager
 * @cdp_update_mac_id: update mac_id for vdev
 */
struct policy_mgr_cdp_cbacks {
	void (*cdp_update_mac_id)(struct wlan_objmgr_psoc *soc,
		uint8_t vdev_id, uint8_t mac_id);
};

/**
 * struct policy_mgr_wma_cbacks - WMA Callbacks to be invoked
 * from policy manager
 * @wma_get_connection_info: Get the connection related info
 *                         from wma table
 * @wma_is_service_enabled: check if certain service is enabled
 *                        by FW
 */
struct policy_mgr_wma_cbacks {
	QDF_STATUS (*wma_get_connection_info)(uint8_t vdev_id,
		struct policy_mgr_vdev_entry_info *conn_table_entry);
	bool (*wma_is_service_enabled)(WMI_SERVICE service_type);
};

/**
 * policy_mgr_need_opportunistic_upgrade() - Tells us if we really
 * need an upgrade to 2x2
 * @psoc: PSOC object information
 * This function returns if updrade to 2x2 is needed
 *
 * Return: PM_NOP = upgrade is not needed, otherwise upgrade is
 * needed
 */
enum policy_mgr_conc_next_action policy_mgr_need_opportunistic_upgrade(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_next_actions() - initiates actions needed on current
 * connections once channel has been decided for the new
 * connection
 * @psoc: PSOC object information
 * @session_id: Session id
 * @action: action to be executed
 * @reason: Reason for connection update
 *
 * This function initiates initiates actions
 * needed on current connections once channel has been decided
 * for the new connection. Notifies UMAC & FW as well
 *
 * Return: QDF_STATUS enum
 */
QDF_STATUS policy_mgr_next_actions(struct wlan_objmgr_psoc *psoc,
		uint32_t session_id,
		enum policy_mgr_conc_next_action action,
		enum policy_mgr_conn_update_reason reason);

/**
 * policy_mgr_set_dual_mac_scan_config() - Set the dual MAC scan config
 * @psoc: PSOC object information
 * @dbs_val: Value of DBS bit
 * @dbs_plus_agile_scan_val: Value of DBS plus agile scan bit
 * @single_mac_scan_with_dbs_val: Value of Single MAC scan with DBS
 *
 * Set the values of scan config. For FW mode config, the existing values
 * will be retained
 *
 * Return: None
 */
void policy_mgr_set_dual_mac_scan_config(struct wlan_objmgr_psoc *psoc,
		uint8_t dbs_val,
		uint8_t dbs_plus_agile_scan_val,
		uint8_t single_mac_scan_with_dbs_val);

/**
 * policy_mgr_set_dual_mac_fw_mode_config() - Set the dual mac FW mode config
 * @psoc: PSOC object information
 * @dbs: DBS bit
 * @dfs: Agile DFS bit
 *
 * Set the values of fw mode config. For scan config, the existing values
 * will be retain.
 *
 * Return: None
 */
void policy_mgr_set_dual_mac_fw_mode_config(struct wlan_objmgr_psoc *psoc,
		uint8_t dbs, uint8_t dfs);

/**
 * policy_mgr_soc_set_dual_mac_cfg_cb() - Callback for set dual mac config
 * @status: Status of set dual mac config
 * @scan_config: Current scan config whose status is the first param
 * @fw_mode_config: Current FW mode config whose status is the first param
 *
 * Callback on setting the dual mac configuration
 *
 * Return: None
 */
void policy_mgr_soc_set_dual_mac_cfg_cb(enum set_hw_mode_status status,
		uint32_t scan_config, uint32_t fw_mode_config);

/**
 * policy_mgr_map_concurrency_mode() - to map concurrency mode
 * between sme and hdd
 * @old_mode: sme provided adapter mode
 * @new_mode: hdd provided concurrency mode
 *
 * This routine will map concurrency mode between sme and hdd
 *
 * Return: true or false
 */
bool policy_mgr_map_concurrency_mode(enum tQDF_ADAPTER_MODE *old_mode,
		enum policy_mgr_con_mode *new_mode);

/**
 * policy_mgr_get_channel_from_scan_result() - to get channel from scan result
 * @psoc: PSOC object information
 * @roam_profile: pointer to roam profile
 * @channel: channel to be filled
 *
 * This routine gets channel which most likely a candidate to which STA
 * will make connection.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_channel_from_scan_result(
		struct wlan_objmgr_psoc *psoc,
		void *roam_profile, uint8_t *channel);

/**
 * policy_mgr_concurrent_open_sessions_running() - Checks for
 * concurrent open session
 *
 * Checks if more than one open session is running for all the allowed modes
 * in the driver
 *
 * Return: True if more than one open session exists, False otherwise
 */
bool policy_mgr_concurrent_open_sessions_running(void);

/**
 * policy_mgr_max_concurrent_connections_reached() - Check if
 * max conccurrency is reached
 * @psoc: PSOC object information
 * Checks for presence of concurrency where more than one connection exists
 *
 * Return: True if the max concurrency is reached, False otherwise
 *
 * Example:
 *    STA + STA (wlan0 and wlan1 are connected) - returns true
 *    STA + STA (wlan0 connected and wlan1 disconnected) - returns false
 *    DUT with P2P-GO + P2P-CLIENT connection) - returns true
 *
 */
bool policy_mgr_max_concurrent_connections_reached(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_clear_concurrent_session_count() - Clear active session count
 * @psoc: PSOC object information
 * Clears the active session count for all modes
 *
 * Return: None
 */
void policy_mgr_clear_concurrent_session_count(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_is_multiple_active_sta_sessions() - Check for
 * multiple STA connections
 *
 * Checks if multiple active STA connection are in the driver
 *
 * Return: True if multiple STA sessions are present, False otherwise
 *
 */
bool policy_mgr_is_multiple_active_sta_sessions(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_is_sta_active_connection_exists() - Check if a STA
 * connection is active
 *
 * Checks if there is atleast one active STA connection in the driver
 *
 * Return: True if an active STA session is present, False otherwise
 */
bool policy_mgr_is_sta_active_connection_exists(void);

/**
 * policy_mgr_concurrent_beaconing_sessions_running() - Checks
 * for concurrent beaconing entities
 *
 * Checks if multiple beaconing sessions are running i.e., if SAP or GO or IBSS
 * are beaconing together
 *
 * Return: True if multiple entities are beaconing together, False otherwise
 */
bool policy_mgr_concurrent_beaconing_sessions_running(void);

/**
 * policy_mgr_wait_for_connection_update() - Wait for hw mode
 * command to get processed
 * @psoc: PSOC object information
 * Waits for CONNECTION_UPDATE_TIMEOUT duration until the set hw mode
 * response sets the event connection_update_done_evt
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_wait_for_connection_update(
		struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_reset_connection_update() - Reset connection
 * update event
 * @psoc: PSOC object information
 * Resets the concurrent connection update event
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_reset_connection_update(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_set_connection_update() - Set connection update
 * event
 * @psoc: PSOC object information
 * Sets the concurrent connection update event
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_set_connection_update(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_restart_opportunistic_timer() - Restarts opportunistic timer
 * @psoc: PSOC object information
 * @check_state: check timer state if this flag is set, else restart
 *               irrespective of state
 *
 * Restarts opportunistic timer for DBS_OPPORTUNISTIC_TIME seconds.
 * Check if current state is RUNNING if check_state is set, else
 * restart the timer irrespective of state.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_restart_opportunistic_timer(
		struct wlan_objmgr_psoc *psoc, bool check_state);

/**
 * policy_mgr_modify_sap_pcl_based_on_mandatory_channel() -
 * Modify SAPs PCL based on mandatory channel list
 * @psoc: PSOC object information
 * @pcl_list_org: Pointer to the preferred channel list to be trimmed
 * @weight_list_org: Pointer to the weights of the preferred channel list
 * @pcl_len_org: Pointer to the length of the preferred chanel list
 *
 * Modifies the preferred channel list of SAP based on the mandatory channel
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_modify_sap_pcl_based_on_mandatory_channel(
		struct wlan_objmgr_psoc *psoc, uint8_t *pcl_list_org,
		uint8_t *weight_list_org, uint32_t *pcl_len_org);

/**
 * policy_mgr_update_and_wait_for_connection_update() - Update and wait for
 * connection update
 * @psoc: PSOC object information
 * @session_id: Session id
 * @channel: Channel number
 * @reason: Reason for connection update
 *
 * Update the connection to either single MAC or dual MAC and wait for the
 * update to complete
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_update_and_wait_for_connection_update(
		struct wlan_objmgr_psoc *psoc, uint8_t session_id,
		uint8_t channel, enum policy_mgr_conn_update_reason reason);

/**
 * policy_mgr_is_sap_mandatory_channel_set() - Checks if SAP
 * mandatory channel is set
 * @psoc: PSOC object information
 * Checks if any mandatory channel is set for SAP operation
 *
 * Return: True if mandatory channel is set, false otherwise
 */
bool policy_mgr_is_sap_mandatory_channel_set(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_list_has_24GHz_channel() - Check if list contains 2.4GHz channels
 * @channel_list: Channel list
 * @list_len: Length of the channel list
 *
 * Checks if the channel list contains atleast one 2.4GHz channel
 *
 * Return: True if 2.4GHz channel is present, false otherwise
 */
bool policy_mgr_list_has_24GHz_channel(uint8_t *channel_list,
		uint32_t list_len);

/**
 * policy_mgr_get_valid_chans() - Get the valid channel list
 * @psoc: PSOC object information
 * @chan_list: Pointer to the valid channel list
 * @list_len: Pointer to the length of the valid channel list
 *
 * Gets the valid channel list filtered by band
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_valid_chans(struct wlan_objmgr_psoc *psoc,
		uint8_t *chan_list, uint32_t *list_len);

/**
 * policy_mgr_get_nss_for_vdev() - Get the allowed nss value for the
 * vdev
 * @psoc: PSOC object information
 * @dev_mode: connection type.
 * @nss2g: Pointer to the 2G Nss parameter.
 * @nss5g: Pointer to the 5G Nss parameter.
 *
 * Fills the 2G and 5G Nss values based on connection type.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_nss_for_vdev(struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_con_mode mode,
		uint8_t *nss_2g, uint8_t *nss_5g);

/**
 * policy_mgr_get_sap_mandatory_channel() - Get the mandatory channel for SAP
 * @psoc: PSOC object information
 * @chan: Pointer to the SAP mandatory channel
 *
 * Gets the mandatory channel for SAP operation
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_sap_mandatory_channel(struct wlan_objmgr_psoc *psoc,
		uint32_t *chan);

/**
 * policy_mgr_set_sap_mandatory_channels() - Set the mandatory channel for SAP
 * @psoc: PSOC object information
 * @channels: Channel list to be set
 * @len: Length of the channel list
 *
 * Sets the channels for the mandatory channel list along with the length of
 * of the channel list.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_set_sap_mandatory_channels(struct wlan_objmgr_psoc *psoc,
		uint8_t *channels, uint32_t len);
#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
/**
 * policy_mgr_register_sap_restart_channel_switch_cb() -
 * Register callback for SAP channel switch without restart
 * @psoc: PSOC object information
 * @sap_restart_chan_switch_cb: Callback to perform channel switch
 *
 * Registers callback to perform channel switch without having to actually
 * restart the beaconing entity
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_register_sap_restart_channel_switch_cb(
		struct wlan_objmgr_psoc *psoc,
		void (*sap_restart_chan_switch_cb)(void *, uint32_t, uint32_t));

/**
 * policy_mgr_deregister_sap_restart_channel_switch_cb() -
 * De-Register callback for SAP channel switch without restart
 * @psoc: PSOC object information
 * De Registers callback to perform channel switch
 *
 * Return: QDF_STATUS Enumeration
 */
QDF_STATUS policy_mgr_deregister_sap_restart_channel_switch_cb(
		struct wlan_objmgr_psoc *psoc);
#endif

/**
 * policy_mgr_is_any_mode_active_on_band_along_with_session() -
 * Check if any connection mode is active on a band along with
 * the given session
 * @psoc: PSOC object information
 * @session_id: Session along which active sessions are looked for
 * @band: Operating frequency band of the connection
 * POLICY_MGR_BAND_24: Looks for active connection on 2.4 GHz only
 * POLICY_MGR_BAND_5: Looks for active connection on 5 GHz only
 *
 * Checks if any of the connection mode is active on a given frequency band
 *
 * Return: True if any connection is active on a given band, false otherwise
 */
bool policy_mgr_is_any_mode_active_on_band_along_with_session(
		struct wlan_objmgr_psoc *psoc, uint8_t session_id,
		enum policy_mgr_band band);

/**
 * policy_mgr_get_mac_id_by_session_id() - Get MAC ID for a given session ID
 * @psoc: PSOC object information
 * @session_id: Session ID
 * @mac_id: Pointer to the MAC ID
 *
 * Gets the MAC ID for a given session ID
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_mac_id_by_session_id(struct wlan_objmgr_psoc *psoc,
		uint8_t session_id, uint8_t *mac_id);

/**
 * policy_mgr_get_mcc_session_id_on_mac() - Get MCC session's ID
 * @psoc: PSOC object information
 * @mac_id: MAC ID on which MCC session needs to be found
 * @session_id: Session with which MCC combination needs to be found
 * @mcc_session_id: Pointer to the MCC session ID
 *
 * Get the session ID of the MCC interface
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_mcc_session_id_on_mac(struct wlan_objmgr_psoc *psoc,
		uint8_t mac_id, uint8_t session_id,
		uint8_t *mcc_session_id);

/**
 * policy_mgr_get_mcc_operating_channel() - Get the MCC channel
 * @psoc: PSOC object information
 * @session_id: Session ID with which MCC is being done
 *
 * Gets the MCC channel for a given session ID.
 *
 * Return: '0' (INVALID_CHANNEL_ID) or valid channel number
 */
uint8_t policy_mgr_get_mcc_operating_channel(struct wlan_objmgr_psoc *psoc,
		uint8_t session_id);

/**
 * policy_mgr_get_pcl_for_existing_conn() - Get PCL for existing connection
 * @psoc: PSOC object information
 * @mode: Connection mode of type 'policy_mgr_con_mode'
 * @pcl_ch: Pointer to the PCL
 * @len: Pointer to the length of the PCL
 * @pcl_weight: Pointer to the weights of the PCL
 * @weight_len: Max length of the weights list
 *
 * Get the PCL for an existing connection
 *
 * Return: None
 */
QDF_STATUS policy_mgr_get_pcl_for_existing_conn(struct wlan_objmgr_psoc *psoc,
		enum policy_mgr_con_mode mode,
		uint8_t *pcl_ch, uint32_t *len,
		uint8_t *weight_list, uint32_t weight_len);

/**
 * policy_mgr_get_valid_chan_weights() - Get the weightage for
 * all valid channels
 * @psoc: PSOC object information
 * @weight: Pointer to the structure containing pcl, saved channel list and
 * weighed channel list
 *
 * Provides the weightage for all valid channels. This compares the PCL list
 * with the valid channel list. The channels present in the PCL get their
 * corresponding weightage and the non-PCL channels get the default weightage
 * of WEIGHT_OF_NON_PCL_CHANNELS.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_get_valid_chan_weights(struct wlan_objmgr_psoc *psoc,
		struct policy_mgr_pcl_chan_weights *weight);

/**
 * policy_mgr_set_hw_mode_on_channel_switch() - Set hw mode
 * after channel switch
 * @session_id: Session ID
 *
 * Sets hw mode after doing a channel switch
 *
 * Return: QDF_STATUS
 */
QDF_STATUS policy_mgr_set_hw_mode_on_channel_switch(
		struct wlan_objmgr_psoc *psoc, uint8_t session_id);

/**
 * policy_mgr_set_do_hw_mode_change_flag() - Set flag to indicate hw mode change
 * @psoc: PSOC object information
 * @flag: Indicate if hw mode change is required or not
 *
 * Set the flag to indicate whether a hw mode change is required after a
 * vdev up or not. Flag value of true indicates that a hw mode change is
 * required after vdev up.
 *
 * Return: None
 */
void policy_mgr_set_do_hw_mode_change_flag(struct wlan_objmgr_psoc *psoc,
		bool flag);

/**
 * policy_mgr_is_hw_mode_change_after_vdev_up() - Check if hw
 * mode change is needed
 * @psoc: PSOC object information
 * Returns the flag which indicates if a hw mode change is required after
 * vdev up.
 *
 * Return: True if hw mode change is required, false otherwise
 */
bool policy_mgr_is_hw_mode_change_after_vdev_up(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_checkn_update_hw_mode_single_mac_mode() - Set hw_mode to SMM
 * if required
 * @psoc: PSOC object information
 * @channel: channel number for the new STA connection
 *
 * After the STA disconnection, if the hw_mode is in DBS and the new STA
 * connection is coming in the band in which existing connections are
 * present, then this function stops the dbs opportunistic timer and sets
 * the hw_mode to Single MAC mode (SMM).
 *
 * Return: None
 */
void policy_mgr_checkn_update_hw_mode_single_mac_mode(
		struct wlan_objmgr_psoc *psoc, uint8_t channel);

/**
 * policy_mgr_dump_connection_status_info() - Dump the concurrency information
 * @psoc: PSOC object information
 * Prints the concurrency information such as tx/rx spatial stream, chainmask,
 * etc.
 *
 * Return: None
 */
void policy_mgr_dump_connection_status_info(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_mode_specific_connection_count() - provides the
 * count of connections of specific mode
 * @psoc: PSOC object information
 * @mode: type of connection
 * @list: To provide the indices on pm_conc_connection_list
 *	(optional)
 *
 * This function provides the count of current connections
 *
 * Return: connection count of specific type
 */
uint32_t policy_mgr_mode_specific_connection_count(
		struct wlan_objmgr_psoc *psoc, enum policy_mgr_con_mode mode,
		uint32_t *list);

/**
 * policy_mgr_hw_mode_transition_cb() - Callback for HW mode
 * transition from FW
 * @old_hw_mode_index: Old HW mode index
 * @new_hw_mode_index: New HW mode index
 * @num_vdev_mac_entries: Number of vdev-mac id mapping that follows
 * @vdev_mac_map: vdev-mac id map. This memory will be freed by the caller.
 * So, make local copy if needed.
 *
 * Provides the old and new HW mode index set by the FW
 *
 * Return: None
 */
void policy_mgr_hw_mode_transition_cb(uint32_t old_hw_mode_index,
		uint32_t new_hw_mode_index,
		uint32_t num_vdev_mac_entries,
		struct policy_mgr_vdev_mac_map *vdev_mac_map,
		struct wlan_objmgr_psoc *context);

/**
 * policy_mgr_current_concurrency_is_mcc() - To check the current
 * concurrency combination if it is doing MCC
 * @psoc: PSOC object information
 * This routine is called to check if it is doing MCC
 *
 * Return: True - MCC, False - Otherwise
 */
bool policy_mgr_current_concurrency_is_mcc(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_register_sme_cb() - register SME callbacks
 * @psoc: PSOC object information
 * @sme_cbacks: function pointers from SME
 *
 * API, allows SME to register callbacks to be invoked by policy
 * mgr
 *
 * Return: SUCCESS,
 *         Failure (if registration fails)
 */
QDF_STATUS policy_mgr_register_sme_cb(struct wlan_objmgr_psoc *psoc,
		struct policy_mgr_sme_cbacks *sme_cbacks);

/**
 * policy_mgr_register_tdls_cb() - register TDLS callbacks
 * @psoc: PSOC object information
 * @tdls_cbacks: function pointers from TDLS
 *
 * API, allows TDLS to register callbacks to be invoked by
 * policy mgr
 *
 * Return: SUCCESS,
 *         Failure (if registration fails)
 */
QDF_STATUS policy_mgr_register_tdls_cb(struct wlan_objmgr_psoc *psoc,
		struct policy_mgr_tdls_cbacks *tdls_cbacks);

/**
 * policy_mgr_register_cdp_cb() - register CDP callbacks
 * @psoc: PSOC object information
 * @cdp_cbacks: function pointers from CDP
 *
 * API, allows CDP to register callbacks to be invoked by
 * policy mgr
 *
 * Return: SUCCESS,
 *         Failure (if registration fails)
 */
QDF_STATUS policy_mgr_register_cdp_cb(struct wlan_objmgr_psoc *psoc,
		struct policy_mgr_cdp_cbacks *cdp_cbacks);

/**
 * policy_mgr_register_wma_cb() - register WMA callbacks
 * @psoc: PSOC object information
 * @wma_cbacks: function pointers from WMA
 *
 * API, allows WMA to register callbacks to be invoked by policy
 * mgr
 *
 * Return: SUCCESS,
 *         Failure (if registration fails)
 */
QDF_STATUS policy_mgr_register_wma_cb(struct wlan_objmgr_psoc *psoc,
		struct policy_mgr_wma_cbacks *wma_cbacks);

/**
 * policy_mgr_is_dbs_enable() - Check if master DBS control is enabled
 * @psoc: PSOC object information
 * Checks if the master DBS control is enabled. This will be used
 * to override any other DBS capability
 *
 * Return: True if master DBS control is enabled
 */
bool policy_mgr_is_dbs_enable(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_is_hw_dbs_capable() - Check if HW is DBS capable
 * @psoc: PSOC object information
 * Checks if the HW is DBS capable
 *
 * Return: true if the HW is DBS capable
 */
bool policy_mgr_is_hw_dbs_capable(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_is_hw_sbs_capable() - Check if HW is SBS capable
 * @psoc: PSOC object information
 * Checks if the HW is SBS capable
 *
 * Return: true if the HW is SBS capable
 */
bool policy_mgr_is_hw_sbs_capable(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_is_current_hwmode_dbs() - Check if current hw mode is DBS
 * @psoc: PSOC object information
 * Checks if current hardware mode of the system is DBS or no
 *
 * Return: true or false
 */
bool policy_mgr_is_current_hwmode_dbs(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_is_hw_dbs_2x2_capable() - if hardware is capable of dbs 2x2
 * @psoc: PSOC object information
 * This function checks if hw_modes supported are always capable of
 * DBS 2x2.
 *    true: DBS 2x2 can always be supported
 *    false: hw_modes support DBS 1x1 as well
 *
 * Return: true - DBS2x2, false - DBS1x1
 */
bool policy_mgr_is_hw_dbs_2x2_capable(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_init() - Policy Manager component initialization
 *                 routine
 *
 * Return - QDF Status
 */
QDF_STATUS policy_mgr_init(void);

/**
 * policy_mgr_deinit() - Policy Manager component
 *                 de-initialization routine
 *
 * Return - QDF Status
 */
QDF_STATUS policy_mgr_deinit(void);

/**
 * policy_mgr_psoc_enable() - Policy Manager component
 *                 enable routine
 * @psoc: PSOC object information
 *
 * Return - QDF Status
 */
QDF_STATUS policy_mgr_psoc_enable(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_psoc_disable() - Policy Manager component
 *                 disable routine
 * @psoc: PSOC object information
 *
 * Return - QDF Status
 */
QDF_STATUS policy_mgr_psoc_disable(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_psoc_open() - Policy Manager component
 *                 open routine
 * @psoc: PSOC object information
 *
 * Return - QDF Status
 */
QDF_STATUS policy_mgr_psoc_open(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_psoc_close() - Policy Manager component
 *                 close routine
 * @psoc: PSOC object information
 *
 * Return - QDF Status
 */
QDF_STATUS policy_mgr_psoc_close(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_get_num_dbs_hw_modes() - Get number of HW mode
 * @psoc: PSOC object information
 * Fetches the number of DBS HW modes returned by the FW
 *
 * Return: Negative value on error or returns the number of DBS HW modes
 */
int8_t policy_mgr_get_num_dbs_hw_modes(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_get_dbs_hw_modes() - Get the DBS HW modes for userspace
 * @psoc: PSOC object information
 * @one_by_one_dbs: 1x1 DBS capability of HW
 * @two_by_two_dbs: 2x2 DBS capability of HW
 *
 * Provides the DBS HW mode capability such as whether
 * 1x1 DBS, 2x2 DBS is supported by the HW or not.
 *
 * Return: Failure in case of error and 0 on success
 *         one_by_one_dbs/two_by_two_dbs will be false,
 *         if they are not supported.
 *         one_by_one_dbs/two_by_two_dbs will be true,
 *         if they are supported.
 *         false values of one_by_one_dbs/two_by_two_dbs,
 *         indicate DBS is disabled
 */
QDF_STATUS policy_mgr_get_dbs_hw_modes(struct wlan_objmgr_psoc *psoc,
		bool *one_by_one_dbs, bool *two_by_two_dbs);

/**
 * policy_mgr_check_sta_ap_concurrent_ch_intf() - Restart SAP in STA-AP case
 * @data: Pointer to STA adapter
 *
 * Restarts the SAP interface in STA-AP concurrency scenario
 *
 * Restart: None
 */
void policy_mgr_check_sta_ap_concurrent_ch_intf(void *data);

/**
 * policy_mgr_get_current_hw_mode() - Get current HW mode params
 * @psoc: PSOC object information
 * @hw_mode: HW mode parameters
 *
 * Provides the current HW mode parameters if the HW mode is initialized
 * in the driver
 *
 * Return: Success if the current HW mode params are successfully populated
 */
QDF_STATUS policy_mgr_get_current_hw_mode(struct wlan_objmgr_psoc *psoc,
		struct policy_mgr_hw_mode_params *hw_mode);

/**
 * policy_mgr_get_dbs_plus_agile_scan_config() - Get DBS plus agile scan bit
 * @psoc: PSOC object information
 * Gets the DBS plus agile scan bit of concurrent_scan_config_bits
 *
 * Return: 0 or 1 to indicate the DBS plus agile scan bit
 */
bool policy_mgr_get_dbs_plus_agile_scan_config(struct wlan_objmgr_psoc *psoc);

/**
 * policy_mgr_get_single_mac_scan_with_dfs_config() - Get Single
 * MAC scan with DFS bit
 * @psoc: PSOC object information
 * Gets the Single MAC scan with DFS bit of concurrent_scan_config_bits
 *
 * Return: 0 or 1 to indicate the Single MAC scan with DFS bit
 */
bool policy_mgr_get_single_mac_scan_with_dfs_config(
		struct wlan_objmgr_psoc *psoc);
#endif /* __WLAN_POLICY_MGR_API_H */