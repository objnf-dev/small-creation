#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/init_task.h>

// Must use "void" to prevent warning
static int __init _module_init(void) {
  struct task_struct *process;
  process = &init_task;  // init/init_task.c#L56
  printk(KERN_INFO"                 CMD    PID   PPID STATUS   PRIO   KERN\n");
  for_each_process(process) {    // linux/sched/singal.h#L565
    // include/linux/sched.h#L629; include/linux/mm_types.h#L375
    // Kernel threads have no mm_struct
    if(process -> mm == NULL) {
      printk(KERN_INFO"%20s %6d %6d %6ld %6d      Y\n", process -> comm, process -> pid,  \
      process -> parent -> pid, process -> state, process -> prio);
    } else {
      printk(KERN_INFO"%20s %6d %6d %6ld %6d      N\n", process -> comm, process -> pid,  \
      process -> parent -> pid, process -> state, process -> prio);
    }
  }
  return 0;
}

static void __exit _module_exit(void) {
  printk(KERN_INFO"Module written by 18271241.\n");    // Add a '\n' to flush buffer.
}


// Load module
MODULE_LICENSE("GPL");
module_init(_module_init);
module_exit(_module_exit);
