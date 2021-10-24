/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * syscalls.h - Linux syscall interfaces (non-arch-specific)
 *
 * Copyright (c) 2004 Randy Dunlap
 * Copyright (c) 2004 Open Source Development Labs
 */

/* obsolete: Self-defined System calls. */
asmlinkage int setnice_zwt(pid_t pid, int flag, int nicevalue, 
							void __user * prio, void __user * nice);

