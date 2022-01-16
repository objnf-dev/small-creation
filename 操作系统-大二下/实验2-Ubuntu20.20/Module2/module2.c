#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

static pid_t pid = 1;
module_param(pid, int, S_IRUGO);    // include/linux/stat.h#L11, 0444, type has special rules.

static int __init _module_init(void) {
    struct task_struct *process, *currentItem;
    struct list_head *item;    // include/linux/types.h#L176
    process = pid_task(find_get_pid(pid), PIDTYPE_PID);
    printk(KERN_INFO"Current process name: %s, pid: %d.\n", process -> comm, process -> pid);
    
    // Parent
    if (process -> parent == NULL)
        printk(KERN_ALERT"This process has no parent process.\n");
    else
        printk(KERN_INFO"The parent process name: %s, pid: %d.\n", process -> parent -> comm, process -> parent -> pid);
    
    // Siblings
    list_for_each(item, &process -> parent -> children) {     // include/linux/list.h#L552
        currentItem = list_entry(item, struct task_struct, sibling);
        printk(KERN_INFO"Sibling process name: %s, pid: %d.\n", currentItem -> comm, currentItem -> pid);
    }
    
    // Children
    list_for_each(item, &process -> children) {
        currentItem = list_entry(item, struct task_struct, sibling);
        printk(KERN_INFO"Child process name: %s, pid: %d.\n", currentItem -> comm, currentItem -> pid);
    }
    
    return 0;
}

static void __exit _module_exit(void) {
    printk(KERN_INFO"Module written by ObjectNF.\n");
}


// Load module
MODULE_LICENSE("GPL");
module_init(_module_init);
module_exit(_module_exit);
