/*
 * Copyright (c) 2011, 2017-2018 The Linux Foundation. All rights reserved.
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

#ifndef _OS_IF_SPECTRAL_NETLINK_H
#define _OS_IF_SPECTRAL_NETLINK_H

#include <net/netlink.h>
#include <wlan_objmgr_pdev_obj.h>

/* NETLINK related declarations */
#if (KERNEL_VERSION(2, 6, 31) > LINUX_VERSION_CODE)
void os_if_spectral_nl_data_ready(struct sock *sk, int len);
#else
void os_if_spectral_nl_data_ready(struct sk_buff *skb);
#endif /* VERSION CHECK */

#ifndef NETLINK_ATHEROS
#define NETLINK_ATHEROS              (NETLINK_GENERIC + 1)
#endif
#define MAX_SPECTRAL_PAYLOAD         1500

/* Init's network namespace */
extern struct net init_net;

/**
 * os_if_spectral_netlink_init() - Initialize Spectral Netlink data structures
 * and register the NL handlers with Spectral target_if
 * @pdev: Pointer to pdev
 *
 * Sending Netlink messages to application layer and de-initialization of
 * netlink related data structures are defined in os_if layer,
 * they need to be registered with Spectral target_if
 *
 * Return: None
 */
void os_if_spectral_netlink_init(struct wlan_objmgr_pdev *pdev);

#endif /* _OS_IF_SPECTRAL_NETLINK_H */