// SPDX-License-Identifier: GPL-2.0
/*
 *  linux/kernel/sys.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */


/* Self-defined Syscalls */
SYSCALL_DEFINE5(setnice_zwt, pid_t, pid, int, flag, int, nicevalue, void __user *, prio,
				void __user *, nice)
{
	// ISO C90 Standard
	struct pid * spid;
	struct task_struct * task;        // include/linux/sched.h#L629
	int nice_pre, nice_post, prio_pre, prio_post;

	if (nicevalue > 19 && nicevalue < -20) {
		printk("Nice value out of range.");
		return EFAULT;
	}

	spid = find_get_pid(pid);        // kernel/pid.c#L435
	task = pid_task(spid, PIDTYPE_PID);        // pid.c#L371, include/linux/pid.h#L9
	nice_pre = task_nice(task);        // include/linux/sched.h#L1612
	prio_pre = task_prio(task);        // kernel/sched/core.c#L4621
	
	if (!flag) {
		copy_to_user(prio, &prio_pre, sizeof(prio_pre));
		copy_to_user(nice, &nice_pre, sizeof(nice_pre));
		printk("Task pid %d nice value is %d.\nPrio value is %d.\n", pid, nice_pre, prio_pre);
		return 0;
	} else {
		set_user_nice(task, nicevalue);        // kernel/sched/core.c#L4509
		nice_post = task_nice(task);
		prio_post = task_prio(task);
		copy_to_user(prio, &prio_post, sizeof(prio_post));
		copy_to_user(nice, &nice_post, sizeof(nice_post));
		printk("Task pid %d nice value changed from %d to %d.\nPrio value is %d.\n", pid, nice_pre, nice_post, prio_post);
		return 0;
	}
}

