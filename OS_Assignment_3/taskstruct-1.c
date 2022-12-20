#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/cred.h>


MODULE_LICENSE("GPL");

struct task_struct *cur_task_struct;
static int cur_pid;
static struct pid *pid_s;

module_param(cur_pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

static int __init taskstruct_1_init(void) {
    pid_s = find_get_pid(cur_pid);
    if (pid_s==NULL) {
        printk(KERN_ERR "wrong pid\n");
        return 0;
    }

    cur_task_struct = pid_task(pid_s, PIDTYPE_PID);
    if (cur_task_struct==NULL) {
        printk(KERN_ERR "error occured!\n");
        return 0;
    }

    printk(KERN_INFO "pid -> %d \n", cur_task_struct->pid);
    printk(KERN_INFO "user_id -> %d\n", cur_task_struct->cred->uid);
    printk(KERN_INFO "pgid -> %d\n", pid_vnr(task_pgrp(cur_task_struct))); //task_tgid_nr(current)
    printk(KERN_INFO "command path -> %s\n", cur_task_struct->comm);

    return 0;
}


static void __exit taskstruct_1_exit(void) {
    printk(KERN_INFO "module removed\n");
}


module_init(taskstruct_1_init);
module_exit(taskstruct_1_exit);